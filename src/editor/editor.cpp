#include "editor.h"

#include <imgui.h>
#include <raylib.h>
#include <vec3.hpp>

#include <vector>
#include <cstring>
#include <sstream>

#include "core.h"
#include "views/views.h"
#include "util/util.h"
#include "imgui/modal.h"
#include "util/parson.h"

namespace editor {

    static std::vector<animation_t*> animations;
    static int animations_selected = 0;
    static char file_open[100] = "";

    // ========== UPDATES ==========

    void initialize() {
        new_animation();
    }

    void update() {
        shortcuts::update();
        
        // title
        char str[50];
        strcpy(str, "sk - ");
        strcat(str, file_open);
        SetWindowTitle(file_is_open() ? str : "sk");

        // drop files
        if (IsFileDropped()) {
            static int files_count = 0;
            modal::open("Import file path: ", GetDroppedFiles(&files_count)[0], editor::import_file, MODAL_TYPE_FILE_OPEN);
            ClearDroppedFiles();
        }

        VIEWS_UPDATE(view);
    }

    void render() {
        // Render background
        animations[animations_selected]->background_render();

        // Render points
        animations[animations_selected]->render_points(view == 2);

        // Render center
        DrawRectangle(-2, -8, 4, 16, COLOR_WHITE50);
        DrawRectangle(-8, -2, 16, 4, COLOR_WHITE50);

        // Render ground
        animations[animations_selected]->ground_render();

        // Render foreground
        animations[animations_selected]->foreground_render();

        // Render view
        VIEWS_RENDER(view);
    }

    void imgui() {
        char str[60];

        animation_t* animation_selected = get_animation();
        ImGui::Text("Animations: ");
        if (ImGui::BeginListBox("Animations", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
            for (int i = 0; i < animations.size(); i++) {
                animation_t* animation = animations[i];
                bool is_selected = i == animations_selected;
                
                util::itoa(str, i);
                strcat(str, ": ");
                strcat(str, animation->get_name());

                if (ImGui::Selectable(str, is_selected) || (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))) {
                    editor::select_animation(i);
                }

                // Drag api
                if (ImGui::IsItemActive() && !ImGui::IsItemHovered()) {
                    int i_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                    if (i_next >= 0 && i_next < animations.size()) {
                        animations[i] = animations[i_next];
                        animations[i_next] = animation;
                        ImGui::ResetMouseDragDelta();
                        editor::select_animation(i_next);
                    }
                }

                if (ImGui::BeginPopupContextItem()) {
                    ImGui::Text("%s", animation->get_name());
                    ImGui::Separator();
                    ImGui::Text("frames[%d]", animation->frame_count());
                    ImGui::Separator();

                    if (ImGui::Button("Delete")) {
                        editor::delete_animation(i);
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();
                }

                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("frames[%d]", animation->frame_count());

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }

        ImGui::Text("Camera properties: ");
        ImGui::DragFloat("X", &camera::camera.target.x, 1.0, 0, 0, "%.0f");
        ImGui::DragFloat("Y", &camera::camera.target.y, 1.0, 0, 0, "%.0f");

        ImGui::Text("Animation[%s] properties: ", animation_selected->get_name());
        ImGui::InputText("name", animation_selected->get_name(), ANIMATION_NAME_LENGTH);
    }

    void destroy() {
        // TODO:
    }

    // ========== TODO: NAME ==========

    void new_point() {
        animation_t* animation = get_animation();
        animation->point_push_back({ 0, 0, 0 });
        animation->selection_empty();
        animation->selection_push_back(animation->point_count() - 1);
    }

    void new_frame() {
        animations[animations_selected]->frame_push_back();
    }

    animation_t* new_animation() {
        animations_selected = animations.size();
        animation_t* animation = new animation_t;
        animations.push_back(animation);
        return animation;
    }

    void new_sprite() {
        get_animation()->foreground_push_back();
    }

    void delete_point(int index) {
        animations[animations_selected]->point_remove(index);
    }

    void delete_frame(int index) {
        animations[animations_selected]->frame_remove(index);
    }

    void delete_animation(int index) {
        animations.erase(animations.begin() + index);

        if (animations.size() == 0) {
            new_animation();
        }

        if (animations_selected >= animations.size()) {
            animations_selected = animations.size() - 1;
        }
    }

    // ========== BACKGROUND ==========

    void background_load(char* path) {
        get_animation()->background_load(path);
    }

    // ========== FILE ==========

    bool file_is_open() {
        return file_open[0] != 0;
    }

    void file_prepend_path(char* str) {
        // TODO: optimize (temp code)
        static char temp[100] = "";

        int pos = fs::get_dir(file_open);
        pos++;
        strncpy(temp, file_open, pos);
        temp[pos] = '\0';
        strcat(temp, str);
        strcpy(str, temp);
    }

    void create_new(char* str) {
        animations.clear();
        animation_foreground.clear_sprites();
        new_animation();
    }

    void import_file(char* str) {
        JSON_Value* root_val = json_parse_file(str);
        
        if (root_val == NULL) {
            return;
        }
        
        strcpy(file_open, str);
        JSON_Object* root_obj = json_value_get_object(root_val);

        const char* sprite_sheet = json_object_get_string(root_obj, "sprite_sheet");
        int x = json_object_get_number(root_obj, "sprite_x");
        int y = json_object_get_number(root_obj, "sprite_y");
        int scale = json_object_get_number(root_obj, "sprite_scale");
        int sprite_count = json_object_get_number(root_obj, "sprite_count");

        animation_foreground.initialize(sprite_sheet, x, y);
        foreground::scale = scale;
        animation_foreground.clear_sprites();

        JSON_Array* sprite_arr = json_object_get_array(root_obj, "sprite");

        for (int i = 0; i < sprite_count; i++) {
            JSON_Object* sprite_obj = json_array_get_object(sprite_arr, i);

            int foreground_y = json_object_get_number(sprite_obj, "foreground_y");
            float ratio = json_object_get_number(sprite_obj, "ratio");
            int point_a = json_object_get_number(sprite_obj, "point_a");
            int point_b = json_object_get_number(sprite_obj, "point_b");

            animation_foreground.add_sprite(foreground_y, ratio, point_a, point_b);
        }

        int anim_count = json_object_get_number(root_obj, "animation_count");
        JSON_Array* anim_arr = json_object_get_array(root_obj, "animation");

        animations.clear();

        for (int i = 0; i < anim_count; i++) {
            JSON_Object* anim_obj = json_array_get_object(anim_arr, i);
            const char* name = json_object_get_string(anim_obj, "name");
            int fps = json_object_get_number(anim_obj, "fps");
            int count_m = json_object_get_number(anim_obj, "count_m");
            int count_n = json_object_get_number(anim_obj, "count_n");

            animation_t* animation = new_animation();
            strcpy(animation->get_name(), name);
            animation->set_fps(fps);
            animation->set_count_m(count_m);
            animation->set_count_n(count_n);

            JSON_Array* frame_arr = json_object_get_array(anim_obj, "frame");
            
            for (int n = 0; n < animation->get_count_n(); n++) {
                JSON_Array* n_arr = json_array_get_array(frame_arr, n);

                for (int m = 0; m < animation->get_count_m(); m++) {
                    JSON_Object* p_obj = json_array_get_object(n_arr, m);

                    glm::vec3* p = animation->point_get(m, n);

                    p->x = json_object_get_number(p_obj, "x");
                    p->y = json_object_get_number(p_obj, "y");
                    p->z = json_object_get_number(p_obj, "z");
                }
            }
        }
    }

    void export_file(char* str) {
        strcpy(file_open, str);
        
        JSON_Value* root_val = json_value_init_object();
        JSON_Object* root_obj = json_value_get_object(root_val);
        JSON_Value* root_arr_val = json_value_init_array();
        JSON_Array* root_arr = json_value_get_array(root_arr_val);
        
        // Sprites
        json_object_set_string(root_obj, "sprite_sheet", animation_foreground.get_path());
        json_object_set_number(root_obj, "sprite_x", animation_foreground.get_x());
        json_object_set_number(root_obj, "sprite_y", animation_foreground.get_y());
        json_object_set_number(root_obj, "sprite_scale", foreground::scale);
        json_object_set_number(root_obj, "sprite_count", animation_foreground.get_sprites_count());

        JSON_Value* sprite_arr_val = json_value_init_array();
        JSON_Array* sprite_arr = json_value_get_array(sprite_arr_val);
        
        for (int i = 0; i < animation_foreground.get_sprites_count(); i++) {
            JSON_Value* sprite_val = json_value_init_object();
            JSON_Object* sprite_obj = json_value_get_object(sprite_val);

            sprite_t* sprite = animation_foreground.get_sprite(i);

            json_object_set_number(sprite_obj, "foreground_y", sprite->foreground_y);
            json_object_set_number(sprite_obj, "ratio", sprite->ratio);
            json_object_set_number(sprite_obj, "point_a", sprite->point_a);
            json_object_set_number(sprite_obj, "point_b", sprite->point_b);

            json_array_append_value(sprite_arr, sprite_val);
        }

        json_object_set_value(root_obj, "sprite", sprite_arr_val);

        // Animations
        for (int i = 0; i < animations.size(); i++) {
            JSON_Value* anim_val = json_value_init_object();
            JSON_Object* anim_obj = json_value_get_object(anim_val);
            JSON_Value* anim_arr_val = json_value_init_array();
            JSON_Array* anim_arr = json_value_get_array(anim_arr_val);

            animation_t* animation = animations[i];

            json_object_set_string(anim_obj, "name", animation->get_name());
            json_object_set_number(anim_obj, "fps", animation->get_fps());
            json_object_set_number(anim_obj, "count_m", animation->get_count_m());
            json_object_set_number(anim_obj, "count_n", animation->get_count_n());

            for (int n = 0; n < animation->get_count_n(); n++) {
                JSON_Value* frame_arr_val = json_value_init_array();
                JSON_Array* frame_arr = json_value_get_array(frame_arr_val);

                for (int m = 0; m < animation->get_count_m(); m++) {
                    JSON_Value* p_val = json_value_init_object();
                    JSON_Object* p_obj = json_value_get_object(p_val);

                    glm::vec3* p = animation->point_get(m, n);

                    json_object_set_number(p_obj, "x", p->x);
                    json_object_set_number(p_obj, "y", p->y);
                    json_object_set_number(p_obj, "z", p->z);

                    json_array_append_value(frame_arr, p_val);
                }

                json_array_append_value(anim_arr, frame_arr_val);
            }

            json_object_set_value(anim_obj, "frame", anim_arr_val);
            json_array_append_value(root_arr, anim_val);
        }

        json_object_set_number(root_obj, "animation_count", animations.size());
        json_object_set_value(root_obj, "animation", root_arr_val);

        json_serialize_to_file(root_val, str);
        json_value_free(root_val);
    }

    char* get_file_open() {
        return file_open;
    }

    // ========== UTIL ==========

    void select_animation(int index) {
        animations_selected = index;
    }

    animation_t* get_animation() {
        return animations[animations_selected];
    }

}

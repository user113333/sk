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
        
        char str[50];
        strcpy(str, "sk - ");
        strcat(str, file_open);
        SetWindowTitle(file_is_open() ? str : "sk");

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

    void new_animation() {
        animations_selected = animations.size();
        animations.push_back(new animation_t);
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
        new_animation();
    }

    void import_file(char* str) {
        strcpy(file_open, str);
    }

    void export_file(char* str) {
        strcpy(file_open, str);
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

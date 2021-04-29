#include "animation_t.h"

#include <imgui.h>

#include <cstring>
#include <algorithm>

#include "editor.h"
#include "util/util.h"
#include "core.h"
#include "views/views.h"

static glm::vec3 point_null = { 0, 0, 0 };
static int count_m = 0;

// ========== CONSTRUCTS ==========

animation_t::animation_t() {
    vector = vector2d_create(sizeof(glm::vec3), 100, 100);
    frame_push_back();
}

animation_t::~animation_t() {
    vector2d_free(vector);
}

char* animation_t::get_name() {
    return name;
}

// ========== POINTS ==========

void animation_t::point_push_back(glm::vec3 point) {
    vector->count_m = count_m;
    vector2d_push_back_m(vector, &point);
    count_m++;
}

void animation_t::point_remove(int index) {
    vector2d_remove_m(vector, index);
    count_m--;
}

glm::vec3* animation_t::point_get(int index) {
    return (glm::vec3*)vector2d_get(vector, index, current_frame);
}

int animation_t::point_count() {
    return count_m;
}

float animation_t::point_get_lowest() {
    int top_y = 0;
    for (int n = 0; n < vector->count_n; n++) {
        for (int m = 0; m < point_count(); m++) {
            glm::vec3* point = (glm::vec3*)vector2d_get(vector, m, n);
            if (top_y < point->y) {
                top_y = point->y;
            }
        }
    }

    return top_y;
}

// ========== FRAMES ==========

void animation_t::frame_push_back() {
    glm::vec3 temp_point = { 0, 0, 0 };
    vector2d_push_back_n(vector, &temp_point);
    
    if (vector->count_n < 2) {
        return;
    }

    for (int i = 0; i < point_count(); i++) {
        glm::vec3* point1 = (glm::vec3*)vector2d_get(vector, i, vector->count_n - 1);
        glm::vec3* point2 = (glm::vec3*)vector2d_get(vector, i, vector->count_n - 2);
        memcpy(point1, point2, vector->item_size);
    }
}

void animation_t::frame_remove(int index) {
    vector2d_remove_n(vector, index);
}

void animation_t::frame_pop() {
    if (vector->count_n > 1) {
        vector2d_pop_n(vector);
    }

    if (current_frame >= vector->count_n) {
        current_frame = vector->count_n - 1;
    }
}

int animation_t::frame_count() {
    return vector->count_n;
}

// ========== SELECTION ==========

void animation_t::selection_remove(int i) {
    selection.erase(selection.begin() + i);
}

void animation_t::selection_push_back(int val) {
    selection.push_back(val);
}

void animation_t::selection_delete() {
    std::sort(selection.begin(), selection.end());
    std::reverse(selection.begin(), selection.end());
    
    for (int i = 0; i < selection.size(); i++) {
        point_remove(selection[i]);
    }

    selection.clear();
}

void animation_t::selection_empty() {
    selection.clear();
}

void animation_t::selection_all() {
    selection_empty();

    for (int i = 0; i < count_m; i++) {
        selection_push_back(i);
    }
}

bool animation_t::selection_contains(int index) {
    for (int i = 0; i < selection.size(); i++) {
        if (index == selection[i]) {
            return true;
        }
    }

    return false;
}

bool animation_t::selection_is_empty() {
    return selection.size() == 0;
}

int animation_t::selection_size() {
    return selection.size();
}

// ========== FOREGROUND ==========

void animation_t::foreground_push_back() {
    foreground.add_sprite();
}

void animation_t::foreground_load(const char* foreground_path, unsigned int x, unsigned int y) {
    foreground.initialize(foreground_path, x, y);
}

void animation_t::foreground_render() {
    foreground.render(vector, current_frame, 0.0, foreground::rotation, foreground::scale);
}

void animation_t::foreground_imgui() {
    foreground.render_imgui(count_m);
}

void animation_t::foreground_sprites_imgui() {
    foreground.render_sprites_imgui(count_m);
}

// ========== GROUND ==========

void animation_t::ground_update() {
    ground.update();
}

void animation_t::ground_render() {
    ground.render();
}

void animation_t::ground_imgui() {
    ground.imgui();
}

// ========== BACKGROUND ==========

void animation_t::background_update() {
    background.update();
}

void animation_t::background_render() {
    background.render();
}

void animation_t::background_imgui() {
    background.imgui();
}

void animation_t::background_load(char* path) {
    background.load_background(path);
}

// ========== UPDATES ==========

void animation_t::update_select() {
    glm::vec4 select = mouse::select_rect();
    
    if (!editor::precise_select) {
        select.x -= texture_point.width / 2;
        select.y -= texture_point.height / 2;
        select.z += texture_point.width;
        select.w += texture_point.height;
    }

    if (!IsKeyDown(KEY_LEFT_SHIFT)) {
        selection.clear();
    }

    for (int i = 0; i < point_count(); i++) {
        glm::vec3* point = point_get(i);
        if (point->x > select.x && point->x < select.x + select.z && point->y > select.y && point->y < select.y + select.w) {
            selection.push_back(i);
        }
    }
}

void animation_t::update() {
    animation_t* animation = editor::get_animation();

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        if (mouse::is_down() && !mouse::is_locked()) {
            animation->update_move(animation_all_frames);
        }
    } else {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !mouse::is_locked()) {
            animation->update_select();
        }
    }
}

void animation_t::update_move(bool animation_all_frames) {
    glm::vec2 select_delta = mouse::pos_delta();

    for (int i = 0; i < selection.size(); i++) {
        if (animation_all_frames) {
            for (int n = 0; n < vector->count_n; n++) {
                glm::vec3* point = (glm::vec3*) vector2d_get(vector, selection[i], n);
                point->x += select_delta.x;
                point->y += select_delta.y;
            }
        } else {
            glm::vec3* point = (glm::vec3*) vector2d_get(vector, selection[i], current_frame);
            point->x += select_delta.x;
            point->y += select_delta.y;
        }
    }
}

void animation_t::update_move_z(bool animation_all_frames) {
}

void animation_t::render_points() {
    if (!editor::display_points) {
        return;
    }

    char str[10];

    for (int i = 0; i < point_count(); i++) {
        util::itoa(str, i);
        glm::vec3* point = point_get(i);
        DrawTexture(texture_point, point->x - texture_point.width / 2, point->y - texture_point.height / 2, selection_contains(i) ? COLOR_PRIMARY : COLOR_WHITE);
        DrawTextEx(font_main, str, { point->x + texture_point.width / 2, point->y - 5 - texture_point.height / 2 }, font_main.baseSize, 0, COLOR_WHITE);
    }
}

void animation_t::render_select_rect() {
    if (mouse::is_down() && !mouse::is_locked() && !IsKeyDown(KEY_LEFT_CONTROL)) {
        glm::vec4 select = mouse::select_rect();
        DrawRectangle(select.x, select.y, select.z, select.w, COLOR_SELECT);
        DrawRectangleLines(select.x, select.y, select.z, select.w, COLOR_PRIMARY);
    }
}

void animation_t::render_imgui_points() {
    char str[50];
    glm::vec3* point_selected;
    int point_selected_id;
    if (!selection_is_empty()) {
        point_selected = point_get(selection[0]);
        point_selected_id = selection[0];
    } else {
        point_selected = &point_null;
        point_selected_id = -1;
    }

    ImGui::Checkbox("Display points", &editor::display_points);

    ImGui::Text("Points: ");
    static int selected_1 = 0;
    if (ImGui::BeginListBox("Points", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (int i = 0; i < point_count(); i++) {
            bool is_selected = selected_1 == i;
            glm::vec3* point = point_get(i);
            
            util::itoa(str, i);

            if (ImGui::Selectable(str, is_selected) || (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))) {
                selection_empty();
                selection_push_back(i);
                selected_1 = i;
            }

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                selection_empty();
                selection_push_back(i);
                selected_1 = i;
            }

            if (ImGui::BeginPopupContextItem()) {
                ImGui::Text("point(x: %.1f, y: %.1f, z: %.1f)", point->x, point->y, point->z);
                ImGui::Separator();

                if (ImGui::Button("Delete")) {
                    point_remove(i);
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    ImGui::Text("Selected points: ");
    static int selected_2 = 0;
    if (ImGui::BeginListBox("Selected points", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (int i = 0; i < selection_size(); i++) {
            bool is_selected = selected_2 == i;
            int select = selection[i];
            glm::vec3* point = (glm::vec3*)vector2d_get(vector, select, current_frame);
            
            util::itoa(str, select);

            if (ImGui::Selectable(str, is_selected) || (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))) {
                selected_2 = i;
            }

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                selection_empty();
                selection_push_back(select);
                selected_2 = 0;
            }

            if (ImGui::BeginPopupContextItem()) {
                ImGui::Text("point(x: %.1f, y: %.1f, z: %.1f)", point->x, point->y, point->z);
                ImGui::Separator();

                if (ImGui::Button("Select")) {
                    selection_empty();
                    selection_push_back(select);
                    selected_2 = 0;
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::Button("Remove from selection")) {
                    selection_remove(i);
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    ImGui::Text("Point[%d] properties: ", point_selected_id);
    ImGui::DragFloat("x", &point_selected->x, 1, 0, 0, "%0.1f");
    ImGui::DragFloat("y", &point_selected->y, 1, 0, 0, "%0.1f");
    ImGui::DragFloat("z", &point_selected->z, 1, 0, 0, "%0.1f");
}

void animation_t::render_imgui_frames() {
    char str[10];

    ImGui::Text("Frames: ");
    
    if (ImGui::BeginListBox("Frames", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (int i = 0; i < vector->count_n; i++) {
            bool is_selected = current_frame == i;
            
            util::itoa(str, i);

            if (ImGui::Selectable(str, is_selected) || (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))) {
                current_frame = i;
            }

            if (ImGui::BeginPopupContextItem()) {
                ImGui::Text("id: %d", i);
                ImGui::Separator();

                if (ImGui::Button("Delete")) {
                    if (vector->count_n > 1) {
                        vector2d_remove_n(vector, i);
                    }

                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
    if (ImGui::BeginTable("frames", 4)) {
        for (int i = 0; i < vector->count_n; i++) {
            if (i % 4 == 0) {
                ImGui::TableNextRow();
            }

            ImGui::TableNextColumn();

            if (i == current_frame) {
                strcpy(str, "--");
                util::itoa(str + strlen(str), i);
                strcat(str, "--");
            } else {
                util::itoa(str, i);
            }

            if (ImGui::Button(str, { -1, 0 })) {
                current_frame = i;
            }
        }
        ImGui::EndTable();
    }
}

// ========== CLIPBOARD ==========

void animation_t::clipboard_copy() {
    if (selection.size() == 0) {
        return;
    }

    char str[1000];
    str[0] = '~'; // identifyer
    str[1] = selection.size();
    int index = 2;
    for (int i = 0; i < selection.size(); i++) {
        str[index] = selection[i];
        index++;
    }
    
    for (int i = 0; i < selection.size(); i++) {
        glm::vec3* point = (glm::vec3*)vector2d_get(vector, selection[i], current_frame);
        
        *(float*)(str + index) = point->x; index += 4;
        *(float*)(str + index) = point->y; index += 4;
        *(float*)(str + index) = point->z; index += 4;
    }

    clipboard::set(str, 2 + (1 + sizeof(float) * 3) * selection.size());
}

void animation_t::clipboard_paste() {
    char* str = clipboard::get();
    if (str[0] != '~') { // identifyer
        return;
    }

    int count = str[1];
    int index = 2;

    for (int i = 0; i < count; i++) {
        char select = str[index + i];
        glm::vec3* point = (glm::vec3*)vector2d_get(vector, select, current_frame);
        point->x = *(float*)(str + (index + count) + (sizeof(float) * 3 * i) + (sizeof(float) * 0));
        point->y = *(float*)(str + (index + count) + (sizeof(float) * 3 * i) + (sizeof(float) * 1));
        point->z = *(float*)(str + (index + count) + (sizeof(float) * 3 * i) + (sizeof(float) * 2));
    }
}

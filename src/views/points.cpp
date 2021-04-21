#include <imgui.h>

#include <raylib.h>

#include "editor/editor.h"
#include "util/mouse.h"
#include "util/util.h"
#include "core.h"

namespace points {

    static bool all_frames = false;

    void imgui() {
        animation_t* animation = editor::get_animation();
        char str[50];
        glm::vec3 point_selected;
        if (animation->selected.size() > 0) {
            point_selected = *animation->point_get(animation->selected[0]);
        }
        
        ImGui::Checkbox("All Frames", &all_frames);

        strcpy(str, "point[");
        util::itoa(str + strlen(str), animation->selected.size() == 0 ? 0 : animation->selected[0]);
        strcat(str, "]");
        ImGui::DragFloat3(str, (float*)&point_selected, 1);

        ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
        if (ImGui::BeginTable("frames", 4)) {
            for (int i = 0; i < animation->vector->count_n; i++) {
                if (i % 4 == 0) {
                    ImGui::TableNextRow();
                }

                ImGui::TableNextColumn();

                if (i == editor::get_animations_selected()) {
                    strcpy(str, "--");
                    util::itoa(str + strlen(str), i);
                    strcat(str, "--");
                } else {
                    util::itoa(str, i);
                }

                if (ImGui::Button(str, { -1, 0 })) {
                    editor::select_animation(i);
                }
            }
            ImGui::EndTable();
        }
    }

    void update() {
        animation_t* animation = editor::get_animation();
        
        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            if (mouse::is_down() && !mouse::is_locked()) {
                animation->move(all_frames);
            }
        } else {
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !mouse::is_locked()) {
                animation->select();
            }
        }
    }

    void render() {
        if (mouse::is_down() && !mouse::is_locked() && !IsKeyDown(KEY_LEFT_CONTROL)) {
            glm::vec4 select = mouse::select_rect();
            DrawRectangle(select.x, select.y, select.z, select.w, COLOR_SELECT);
            DrawRectangleLines(select.x, select.y, select.z, select.w, COLOR_PRIMARY);
        }
    }

}

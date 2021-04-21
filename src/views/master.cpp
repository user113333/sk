#include <imgui.h>

#include <cstring>
#include <vector>

#include "editor/editor.h"
#include "editor/animation.h"
#include "util/util.h"

using namespace ImGui;

namespace master {

    void imgui() {
        char str[60];

        std::vector<animation_t*>* animations = (std::vector<animation_t*>*)editor::get_animations();
        animation_t* animation_selected = (*animations)[editor::get_animations_selected()];
        if (BeginListBox("Animation", ImVec2(-FLT_MIN, 5 * GetTextLineHeightWithSpacing()))) {
            for (int i = 0; i < animations->size(); i++) {
                animation_t* animation = (*animations)[i];
                bool is_selected = editor::get_animations_selected() == i;
                
                util::itoa(str, i);
                strcat(str, ": ");
                strcat(str, animation->name);

                if (Selectable(str, is_selected)) {
                    editor::select_animation(i);
                }

                // Drag api
                if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
                {
                    int i_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                    if (i_next >= 0 && i_next < animations->size()) {
                        (*animations)[i] = (*animations)[i_next];
                        (*animations)[i_next] = animation;
                        ImGui::ResetMouseDragDelta();
                        editor::select_animation(i_next);
                    }
                }

                if (BeginPopupContextItem()) {
                    Text("%s", animation->name);
                    Separator();
                    Text("points[%d], frames[%d]", animation_selected->vector->count_m, animation_selected->vector->count_n);

                    if (Button("Delete")) {
                        editor::delete_animation(i);
                        CloseCurrentPopup();
                    }

                    EndPopup();
                }

                if (IsItemHovered())
                    SetTooltip("points[%d], frames[%d]", animation_selected->vector->count_m, animation_selected->vector->count_n);

                if (is_selected)
                    SetItemDefaultFocus();
            }
            EndListBox();
        }

        InputText("name", animation_selected->name, IM_ARRAYSIZE(animation_selected->name));
    }
    
    void update() {
    }

    void render() {
    }

}

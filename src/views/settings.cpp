#include <imgui.h>

#include "editor/editor.h"

namespace settings {

    void imgui() {
        if (ImGui::Button("Save settings")) {
            // TODO: here ini parser and save
        }

        ImGui::SameLine();
        ImGui::Text("Settings: ");
        ImGui::Checkbox("Precise select", &editor::precise_select);
    }

}

#include <imgui.h>

#include "editor/editor.h"

namespace settings {

    void imgui() {
        ImGui::Text("Settings: ");
        ImGui::Checkbox("Precise select", &editor::precise_select);
    }

}

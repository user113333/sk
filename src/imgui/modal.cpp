#include "imgui.h"

namespace modal {

    static int open_modal = 0;

    void open() {
        open_modal = 1;
    }

    void update() {
        if (open_modal == 1) {
            open_modal = 0;
            ImGui::OpenPopup("Modal window");
        }

        if (ImGui::BeginPopupModal("Modal window", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
            ImGui::Text("Hello dsjfhds fhjs hfj dshfj hds");
            if (ImGui::Button("Close"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }
    }

}

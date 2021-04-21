#include "imgui.h"

namespace modal {

    static int open_modal = 0;
    static char str0[128] = "Hello, world!";

    void open() {
        open_modal = 1;
    }

    void update() {
        if (open_modal == 1) {
            open_modal = 0;
            ImGui::OpenPopup("Modal window");
        }

        if (ImGui::BeginPopupModal("Modal window", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
            ImGui::InputText("input text", str0, IM_ARRAYSIZE(str0));
            if (ImGui::Button("Continue")) {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }

}

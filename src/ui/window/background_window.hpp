#pragma once

#include <imgui.h>

#include "lib/background.hpp"
#include "window.hpp"
#include "imgui/imgui_layer.hpp"

namespace Sk {
    struct BackgroundWindow : public Window {
        void ImGuiWindow(Sk::Background &background)
        {
            bool open_modal = false;
            if (!m_open) return;
            ImGui::Begin("Background Window", &m_open, ImGuiWindowFlags_MenuBar);
            if (ImGui::BeginMenuBar()) {
                if (ImGui::MenuItem("Load new")) {
                    open_modal = true;
                }
                ImGui::EndMenuBar();
            }
            ImGui::End();

            if (open_modal) { 
                ImGui::OpenPopup("Background modal");
            }

            std::optional<std::string> res = 
                imgui_layer::DrawModalFileRead("Background modal", "Load background: ", {"GIF files (.gif)", "*.gif"});

            if (res.has_value()) {
                std::string rfile_name = res.value();
                background.Load(rfile_name);
            }
        }

        void ImGuiCheckbox() {
            ImGui::Checkbox("Background Window", &m_open);
        }
    };
}

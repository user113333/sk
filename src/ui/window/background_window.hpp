#pragma once

#include <imgui.h>

#include "editor/background.h"
#include "window.hpp"
#include "imgui/imgui_layer.h"

struct BackgroundWindow : public Window {
    void ImGuiWindow(Background background)
    {
        if (!m_open) return;
        ImGui::Begin("Background Window", &m_open, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::MenuItem("Load new")) {
                imgui_layer::Modal.OpenFileRead("Load background: ", {"GIF files (.gif)", "*.gif"}, [&background](std::string path){
                    background.Load(path);
                });
            }
            ImGui::EndMenuBar();
        }
        ImGui::End();
    }

    void ImGuiCheckbox() {
        ImGui::Checkbox("Background Window", &m_open);
    }
};

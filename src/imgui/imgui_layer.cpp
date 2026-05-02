#include "imgui_layer.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <portable-file-dialogs.h>

#include "external/imgui_impl_raylib.h"
#include "external/rlImGui.h"

namespace imgui_layer {

    void Initialize() {
        IMGUI_CHECKVERSION();
        ImGuiContext* g = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        
        ImGui_ImplRaylib_Init();
        
        ImGui::StyleColorsDark();
        // io.Fonts->AddFontFromFileTTF(ASSETS_PATH "plex.ttf", 15.0f);
    }

    void Begin() {
        ImGui_ImplRaylib_ProcessEvents();
        ImGui_ImplRaylib_NewFrame();
        ImGui::NewFrame();
    }

    void End() {
        ImGui::Render();
        ImGui_ImplRaylib_RenderDrawData(ImGui::GetDrawData());
    }

    void Destroy() {
        ImGui_ImplRaylib_Shutdown();
        ImGui::DestroyContext();
    }

    bool IsMouseLocked() {
        ImGuiIO& io = ImGui::GetIO();
        return io.WantCaptureMouse;
    }

    std::optional<char*> DrawModalFileRead(char* modal_name, char* message, std::vector<std::string> filters)
    {
        static char s_inputText[255];

        ImGui::SetNextWindowSizeConstraints({500, 0}, {500, 500});
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal(modal_name, nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
            ImGui::TextWrapped(message);

            if (ImGui::Button("..")) {
                auto f = pfd::open_file("Choose file to read", "", filters, false);

                for (auto const &filename : f.result())
                    strcpy(s_inputText, filename.c_str());
            }

            ImGui::SameLine(0);

            if (ImGui::IsWindowAppearing()) {
                ImGui::SetKeyboardFocusHere(0);
            }
            ImGui::SetNextItemWidth(450);
            ImGui::InputText("##FileName", s_inputText, IM_ARRAYSIZE(s_inputText));
            ImGui::Separator();

            if (ImGui::Button("Cancel [Ctrl+C]") || ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_C)) {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return {};
            }

            ImGui::SameLine(0, -1);
            if (ImGui::Button("Continue [Enter]") || ImGui::IsKeyChordPressed(ImGuiKey_Enter)) {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return {s_inputText};
            }

            ImGui::EndPopup();
        }

        return {};
    }

}

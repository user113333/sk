#include "imgui_layer.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "external/imgui_impl_raylib.h"
#include "external/rlImGui.h"
#include "imgui_modal.h"
#include "ui/ui.h"

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

}

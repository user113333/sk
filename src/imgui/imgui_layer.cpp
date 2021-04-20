#include "imgui.h"
#include "imgui/imgui_impl_raylib.h"
#include "imgui/imgui_impl_opengl3.h"

#include "modal.h"
#include "ui/ui.h"

namespace imgui_layer {

    void initialize() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.IniFilename = nullptr;

        ImGui::StyleColorsClassic();

        ImGui_ImplRaylib_Init();
        ImGui_ImplOpenGL3_Init("#version 130");

        io.Fonts->AddFontFromFileTTF(ASSETS_PATH "plex.ttf", 20.0f);
    }

    void update() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplRaylib_ProcessEvent();
        ImGui_ImplRaylib_NewFrame();
        ImGui::NewFrame();
            
        ui::update();
        modal::update();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void destroy() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplRaylib_Shutdown();
        ImGui::DestroyContext();
    }

}

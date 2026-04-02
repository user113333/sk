#include "ui.h"

#include <imgui.h>
#include <string>

#include "editor.h"
#include "views.hpp"
#include "core.h"
#include "util/camera.h"
#include "imgui/imgui_layer.h"

void Ui::OpenFile()
{
    imgui_layer::Modal.OpenFileRead("Import file path: ", {"JSON files (.json .sk)", "*.json *.sk", "All Files", "*"}, editor::import_file);
}

void Ui::DrawMainMenu()
{
    if (ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_O)) {
        OpenFile();
    }

    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New")) { imgui_layer::Modal.OpenYesNo("All the unsaved changes will be lost! Are you sure you want to continue?", editor::create_new); }
            ImGui::Separator();
            if (ImGui::MenuItem("Open..", "Ctrl+O")) {
                OpenFile();   
            }
            // if (ImGui::MenuItem("Save..", "CTRL+S")) { modal::open("Export file path: ", "out", editor::export_file, MODAL_TYPE_FILE_SAVE); }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            editor::views.ImguiRadioList();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows")) {
            m_windows.ImguiCheckList();

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Animation")) {
            ImGui::Checkbox("All Frames", &animation_all_frames);
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Should the selected points move over all frames the same distance");
            }
            
            ImGui::Separator();

            if (ImGui::MenuItem("New Point", "CTRL+SPACE")) { editor::new_point(); }
            if (ImGui::MenuItem("New Frame", "CTRL+ENTER")) { editor::new_frame(); }
            if (ImGui::MenuItem("New Animation")) { editor::new_animation(); }
            if (ImGui::MenuItem("New Sprite")) { editor::new_sprite(); }

            ImGui::Separator();

            if (ImGui::MenuItem("Delete Selected points", "CTRL+DELTE")) { editor::get_animation()->selection_delete(); }
            if (ImGui::MenuItem("Pop frame", "")) { editor::get_animation()->frame_pop(); }

            ImGui::Separator();

            if (ImGui::MenuItem("Copy selected to clipboard", "CTRL+C")) { editor::get_animation()->clipboard_copy(); }
            if (ImGui::MenuItem("Paste selected from clipboard", "CTRL+V")) { editor::get_animation()->clipboard_paste(); }

            ImGui::EndMenu();
        }

        if (ImGui::Button("Center Camera")) {
            camera::Center();
        }

        std::string active_view = editor::views.GetActiveName();
        ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(active_view.c_str()).x - 30);
        ImGui::Text(active_view.c_str());

        ImGui::EndMainMenuBar();
    }
}

void Ui::Update() {
    DrawMainMenu();
    m_windows.DrawImgui();

    // Maybe put these two into imgui_layer?
    imgui_layer::Modal.Draw();
    if (imgui_layer::ImguiDemoWindowOpen) {
        ImGui::ShowDemoWindow(&imgui_layer::ImguiDemoWindowOpen);
    }
}

#include "ui.hpp"

#include <imgui.h>
#include <string>

#include "lib/pack.hpp"
#include "imgui/imgui_layer.hpp"

using namespace Sk;

void Ui::OpenFile()
{
    // imgui_layer::Modal.OpenFileRead("Import file path: ", {"JSON files (.json .sk)", "*.json *.sk", "All Files", "*"}, pack.);
}

void Ui::DrawMainMenu(Pack &pack, Modes &modes)
{
    if (ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_O)) {
        OpenFile();
    }

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            // if (ImGui::MenuItem("New")) { imgui_layer::Modal.OpenYesNo("All the unsaved changes will be lost! Are you sure you want to continue?", editor::create_new); }
            ImGui::Separator();
            if (ImGui::MenuItem("Open..", "Ctrl+O")) {
                OpenFile();
            }
            // if (ImGui::MenuItem("Save..", "CTRL+S")) { modal::open("Export file path: ", "out", editor::export_file, MODAL_TYPE_FILE_SAVE); }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Modes")) {
            std::vector mode_names = modes.GetNames();
            int active = modes.GetActiveIndex();
            for (int i = 0; i < mode_names.size(); i++) {
                if (ImGui::RadioButton(mode_names[i].c_str(), active == i)) {
                    modes.SetActiveIndex(i);
                }
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows")) {
            m_windows.ImguiCheckList();
            ImGui::Separator();
            ImGui::Checkbox("Imgui Demo Window", &m_imgui_demo_open);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Animation")) {
            // ImGui::Checkbox("All Frames", &animation_all_frames);
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Should the selected points move over all frames the same distance");
            }
            
            ImGui::Separator();

            // if (ImGui::MenuItem("New Point", "CTRL+SPACE")) { editor::new_point(); }
            // if (ImGui::MenuItem("New Frame", "CTRL+ENTER")) { editor::new_frame(); }
            // if (ImGui::MenuItem("New Animation")) { editor::new_animation(); }
            // if (ImGui::MenuItem("New Sprite")) { editor::new_sprite(); }

            ImGui::Separator();

            // if (ImGui::MenuItem("Delete Selected points", "CTRL+DELTE")) { editor::get_animation()->selection_delete(); }
            // if (ImGui::MenuItem("Pop frame", "")) { editor::get_animation()->frame_pop(); }

            ImGui::Separator();

            // if (ImGui::MenuItem("Copy selected to clipboard", "CTRL+C")) { editor::get_animation()->clipboard_copy(); }
            // if (ImGui::MenuItem("Paste selected from clipboard", "CTRL+V")) { editor::get_animation()->clipboard_paste(); }

            ImGui::EndMenu();
        }

        if (ImGui::Button("Center Camera")) {
            // camera::Center();
        }

        std::string active_view = modes.GetActiveName();
        ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(active_view.c_str()).x - 15);
        ImGui::Text("%s", active_view.c_str());

        ImGui::EndMainMenuBar();
    }
}

void Ui::Update(Pack &pack, Modes &modes) {
    DrawMainMenu(pack, modes);
    m_windows.DrawImgui(pack);
    if (m_imgui_demo_open) {
        ImGui::ShowDemoWindow(&m_imgui_demo_open);
    }
}

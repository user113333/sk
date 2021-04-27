#include "ui.h"

#include <imgui.h>

#include "editor/editor.h"
#include "imgui/modal.h"
#include "views/views.h"
#include "core.h"

namespace ui {

    void update() {
        static bool window_demo = false;

        if (!show_imgui) {
            return;
        }

        if (window_demo) {
            ImGui::ShowDemoWindow(&window_demo);
        }

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New")) { modal::open("All the unsaved changes will be lost! Are you sure you want to continue?", "", editor::create_new, MODAL_TYPE_MESSAGE); }
                ImGui::Separator();
                if (ImGui::MenuItem("Open..", "CTRL+O")) { modal::open("Import file path: ", "out", editor::import_file, MODAL_TYPE_FILE_OPEN); }
                if (ImGui::MenuItem("Save..", "CTRL+S")) { modal::open("Export file path: ", "out", editor::export_file, MODAL_TYPE_FILE_SAVE); }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View")) {
                for (int i = 0; i < IM_ARRAYSIZE(views); i++) {
                    ImGui::RadioButton(views[i].name, &editor::view, i);
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window")) {
                for (int i = 0; i < IM_ARRAYSIZE(windows); i++) {
                    if (windows[i].separator) {
                        ImGui::Separator();
                    }

                    if (ImGui::MenuItem(windows[i].name, "", windows[i].imgui_window)) { windows[i].imgui_window = !windows[i].imgui_window; }
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Imgui demo Window", "", window_demo)) { window_demo = !window_demo; }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Animation")) {
                ImGui::Checkbox("All Frames", &animation_all_frames);
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Should the selected points move over all frames the same distance");
                }
                
                ImGui::Separator();

                if (ImGui::MenuItem("New Point", "CTRL+SPACE")) { editor::new_point(); }
                if (ImGui::MenuItem("New Frame")) { editor::new_frame(); }
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

            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(views[editor::view].name).x - 30);
            ImGui::Text(views[editor::view].name);

            ImGui::EndMainMenuBar();
        }

        static int window_flags = ImGuiWindowFlags_NoCollapse;

        for (int i = 0; i < IM_ARRAYSIZE(windows); i++) {
            if (windows[i].imgui_window) {
                ImGui::Begin(windows[i].name, &windows[i].imgui_window, window_flags);
                WINDOWS_IMGUI(i);
                ImGui::End();
            }
        }
    }

}

#include "imgui.h"

#include <raylib.h>

namespace modal {

    static int open_modal = 0;
    static char str0[128] = "Hello, world!";
    static char str1[128] = "Hello, world!";
    void (*callback_input)(char*);
    void (*callback_message)(void);

    void open(const char* message, const char* default_input, void (*callback)(char*)) {
        open_modal = 0b011;
        strcpy(str0, message);
        strcpy(str1, default_input);
        callback_input = callback;
    }

    void open(const char* message, void (*callback)(void)) {
        open_modal = 0b101;
        strcpy(str0, message);
        callback_message = callback;
    }

    void update() {
        if (open_modal & 0b001) {
            open_modal &= 0b110;
            ImGui::OpenPopup("Modal window");
        }

        ImGui::SetNextWindowSizeConstraints({500, 0}, { 500, 500 });
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("Modal window", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
            if (open_modal & 0b010) {
                if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)) {
                    ImGui::SetKeyboardFocusHere(0);
                }
                ImGui::InputText(str0, str1, IM_ARRAYSIZE(str0));

                if (ImGui::Button("Cancel [ESC]") || IsKeyDown(KEY_ESCAPE)) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SameLine(0, -1);
                if (ImGui::Button("Continue [Enter]") || IsKeyDown(KEY_ENTER)) {
                    ImGui::CloseCurrentPopup();
                    callback_input(str1);
                }
            }

            if (open_modal & 0b100) {
                ImGui::TextWrapped(str0);
                ImGui::Separator();
                
                if (ImGui::Button("Cancel [ESC]") || IsKeyDown(KEY_ESCAPE)) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SameLine(0, -1);
                if (ImGui::Button("Continue [Enter]") || IsKeyDown(KEY_ENTER)) {
                    ImGui::CloseCurrentPopup();
                    callback_message();
                }
            }

            ImGui::EndPopup();
        }
    }

}

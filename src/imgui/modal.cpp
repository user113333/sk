#include "modal.h"

#include <imgui.h>
#include <raylib.h>

#include "portable-file-dialogs.h"

namespace modal {

    static int open_modal = 0;
    static char str0[128] = "message";
    static char str1[128] = "input box";
    void (*callback)(char*);

    void open(const char* message, const char* default_input, void (*callback_func)(char*), MODAL_TYPE type) {
        open_modal = type | MODAL_OPEN;
        
        strcpy(str0, message);
        strcpy(str1, default_input);

        callback = callback_func;
    }

    void update() {
        if (open_modal & MODAL_OPEN) {
            open_modal &= MODAL_OPEN_INVERTED;
            ImGui::OpenPopup("Modal window");
        }
        
        // if (open_modal & MODAL_TYPE_MESSAGE) {
        //     ImGui::SetNextWindowSizeConstraints({ 500, 0 }, { 500, 500 });
        // } else {
        //     ImGui::SetNextWindowSizeConstraints({ 300, 0 }, { 500, 500 });
        // }

        ImGui::SetNextWindowSizeConstraints({ 500, 0 }, { 500, 500 });
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("Modal window", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
            if (open_modal & MODAL_TYPE_MESSAGE) {
                ImGui::TextWrapped(str0);
                ImGui::Separator();
                
                if (ImGui::Button("Cancel [ESC]") || IsKeyDown(KEY_ESCAPE)) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SameLine(0, -1);
                if (ImGui::Button("Continue [Enter]") || IsKeyDown(KEY_ENTER)) {
                    ImGui::CloseCurrentPopup();
                    callback("");
                }
            } else {
                if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)) {
                    ImGui::SetKeyboardFocusHere(0);
                }
                
                ImGui::Text(str0);
                
                if (open_modal & (MODAL_TYPE_FILE_SAVE | MODAL_TYPE_FILE_OPEN)) {
                    bool btn = ImGui::Button("..");
                    
                    if (btn && open_modal & MODAL_TYPE_FILE_OPEN) {
                        auto f = pfd::open_file(
                            "Choose file to read",
                            "", // PATH
                            { "All Files", "*" },
                            pfd::opt::force_path);

                        auto res = f.result();
                        if (res.size() > 0) {
                            strcpy(str1, res[0].c_str());
                        }
                    }

                    if (btn && open_modal & MODAL_TYPE_FILE_SAVE) {
                        auto f = pfd::save_file(
                            "Choose file to save",
                            "", // PATH
                            { "All Files", "*" },
                            true);

                        auto res = f.result();
                        strcpy(str1, res.c_str());
                    }

                    ImGui::SameLine(0);
                }
                
                ImGui::SetNextItemWidth(450);
                ImGui::InputText("", str1, IM_ARRAYSIZE(str1));
                ImGui::Separator();

                if (ImGui::Button("Cancel [ESC]") || IsKeyDown(KEY_ESCAPE)) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SameLine(0, -1);
                if (ImGui::Button("Continue [Enter]") || IsKeyDown(KEY_ENTER)) {
                    ImGui::CloseCurrentPopup();
                    callback(str1);
                }
            }

            ImGui::EndPopup();
        }
    }

}

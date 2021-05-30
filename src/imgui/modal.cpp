#include "modal.h"

#include <imgui.h>

#include "pfd/pfd.h"
#include "util/input.h"

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
                
                if (ImGui::Button("Cancel [ESC]") || input::is_key_down(256)) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SameLine(0, -1);
                if (ImGui::Button("Continue [Enter]") || input::is_key_down(257)) {
                    ImGui::CloseCurrentPopup();
                    callback("");
                }
            } else {
                if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)) {
                    ImGui::SetKeyboardFocusHere(0);
                }
                
                ImGui::TextWrapped(str0);
                
                if (open_modal & (MODAL_TYPE_FILE_SAVE | MODAL_TYPE_FILE_OPEN)) {
                    bool btn = ImGui::Button("..");
                    
                    if (btn && open_modal & MODAL_TYPE_FILE_OPEN) {
                        auto f = pfd::open_file("Choose file to read", "", { "JSON files (.json .sk)", "*.json *.sk", "All Files", "*" }, pfd::opt::none);

                        for (auto const &filename : f.result())
                            strcpy(str1, filename.c_str());
                    }

                    if (btn && open_modal & MODAL_TYPE_FILE_SAVE) {
                        auto f = pfd::save_file("Choose file to save to", "", { "JSON files (.json .sk)", "*.json *.sk", "All Files", "*" }, pfd::opt::none);
                        std::string filename = f.result().c_str();
                        if (filename.length() != 0) {
                            strcpy(str1, filename.c_str());
                        }
                    }

                    ImGui::SameLine(0);
                }
                
                ImGui::SetNextItemWidth(450);
                ImGui::InputText("", str1, IM_ARRAYSIZE(str1));
                ImGui::Separator();

                if (ImGui::Button("Cancel [ESC]") || input::is_key_down(256)) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SameLine(0, -1);
                if (ImGui::Button("Continue [Enter]") || input::is_key_down(257)) {
                    ImGui::CloseCurrentPopup();
                    callback(str1);
                }
            }

            ImGui::EndPopup();
        }
    }

    void notify(const char* title, const char* str) {
        pfd::notify::notify(title, str);
    }

}

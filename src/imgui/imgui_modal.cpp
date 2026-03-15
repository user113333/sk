#include "imgui_modal.h"

#include <imgui.h>
#include <portable-file-dialogs.h>

#include "util/input.h"

using namespace ImGui;

void ImGuiModal::Open()
{
    m_openPopup = true;
}

void ImGuiModal::Close()
{
    ImGui::CloseCurrentPopup();
}

void ImGuiModal::OpenYesNo(const char *message, std::function<void(void)> callbackFunction)
{
    Open();
    m_currentType = ImGuiModalType::YesNo;
    m_message = message;
    callbackYesNo = callbackFunction;
}

void ImGuiModal::OpenFileRead(const char* message, std::vector<std::string> dialogFilters, std::function<void(std::string)> callbackFunction)
{
    Open();
    m_currentType = ImGuiModalType::FileRead;
    m_message = message;
    m_dialogFilters = dialogFilters;
    callbackFileRead = callbackFunction;
}

void ImGuiModal::Draw()
{
    if (m_openPopup) {
        OpenPopup("Modal window");
    }

    SetNextWindowSizeConstraints({500, 0}, {500, 500});
    SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    if (BeginPopupModal("Modal window", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
        switch (m_currentType) {
        case ImGuiModalType::YesNo:
            DrawYesNo();
            break;
        case ImGuiModalType::FileRead:
            DrawFileRead();
            break;
        }

        EndPopup();
    }

    m_openPopup = false;
}

void ImGuiModal::DrawYesNo()
{
    ImGui::TextWrapped(m_message);
    ImGui::Separator();

    if (ImGui::Button("Cancel [Ctrl+C]") || ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_C)) {
        Close();
    }

    ImGui::SameLine(0, -1);
    if (ImGui::Button("Continue [Enter]") || ImGui::IsKeyChordPressed(ImGuiKey_Enter)) {
        Close();
        callbackYesNo();
    }
}

void ImGuiModal::DrawFileRead()
{

    ImGui::TextWrapped(m_message);

    if (ImGui::Button("..")) {
        auto f = pfd::open_file("Choose file to read", "", m_dialogFilters, false);

        for (auto const &filename : f.result())
            strcpy(m_inputText, filename.c_str());
    }

    ImGui::SameLine(0);

    if (m_openPopup) {
        ImGui::SetKeyboardFocusHere(0);
    }
    ImGui::SetNextItemWidth(450);
    ImGui::InputText("##FileName", m_inputText, IM_ARRAYSIZE(m_inputText));
    ImGui::Separator();

    if (ImGui::Button("Cancel [Ctrl+C]") || ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_C)) {
        Close();
    }

    ImGui::SameLine(0, -1);
    if (ImGui::Button("Continue [Enter]") || ImGui::IsKeyChordPressed(ImGuiKey_Enter)) {
        Close();
        callbackFileRead(m_inputText);
    }
}

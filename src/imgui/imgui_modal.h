#pragma once

#include <functional>
#include <string>

enum class ImGuiModalType {
    None,
    YesNo,
    FileRead
};

class ImGuiModal {
public:
    ImGuiModal() = default;

    void OpenYesNo(const char* message, std::function<void(void)> callbackFunction);
    void OpenFileRead(const char* message, std::vector<std::string> dialogFilters, std::function<void(std::string)> callbackFunction);
    
    void Draw();
    void DrawYesNo();
    void DrawFileRead();
    
private:
    ImGuiModalType m_currentType = ImGuiModalType::None; // Modal that is currently open
    bool m_openPopup = false;
    const char* m_message;
    char m_inputText[255];
    std::vector<std::string> m_dialogFilters;

    std::function<void(void)> callbackYesNo;
    std::function<void(std::string)> callbackFileRead;

    void Open();
    void Close();
};

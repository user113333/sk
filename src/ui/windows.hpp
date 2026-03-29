#pragma once

#include <vector>
#include <string>

class Windows {
public:
    void DrawImgui();
    void ImguiCheckList();

private:
    const std::vector<std::string> m_window_names = {
        "Master window",
        "Points window",
        "Frames window",
        "Foreground window",
        "Sprites window",
        "Ground window",
        "Background window",
        "Play window",
        "Settings window",
        "Shortcuts window"
    };
};
#pragma once

#include <vector>
#include <string>

#include "window/background_window.hpp"

class Windows {
public:
    void DrawImgui();
    void ImguiCheckList();

private:
    Sk::BackgroundWindow m_background_window;
    // const std::vector<std::string> m_window_names = {
    //     "Master window",
    //     "Points window",
    //     "Frames window",
    //     "Foreground window",
    //     "Sprites window",
    //     "Ground window",
    //     "Background window",
    //     "Play window",
    //     "Settings window",
    //     "Shortcuts window"
    // };
};
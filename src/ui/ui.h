#pragma once

#include "imgui/imgui_modal.h"

namespace ui {
    inline ImGuiModal Modal;
    inline bool window_demo = false;
    inline bool position_windows = false;
    
    void update();
}

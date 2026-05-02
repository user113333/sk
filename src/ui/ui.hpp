#pragma once

#include "windows.hpp"
#include "imgui/imgui_modal.h"
#include "lib/pack.hpp"
#include "../editor/modes.hpp"

class Ui {
public:
    void Update(Sk::Pack &pack);
    
private:
    void OpenFile();
    void DrawMainMenu(Sk::Pack &pack);

    Windows m_windows;
};

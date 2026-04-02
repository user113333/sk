#pragma once

#include "windows.hpp"
#include "imgui/imgui_modal.h"

class Ui {
public:
    void Update();
    
private:
    void OpenFile();
    void DrawMainMenu();

    Windows m_windows;
};

#pragma once

#include "windows.hpp"
#include "lib/pack.hpp"
#include "../editor/modes.hpp"

class Ui {
public:
    void Update(Sk::Pack &pack, Modes &modes);
    
private:
    void OpenFile();
    void DrawMainMenu(Sk::Pack &pack, Modes &modes);

    Windows m_windows;
};

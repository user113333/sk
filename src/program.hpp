#pragma once

#include "ui/ui.hpp"
#include "editor/editor.hpp"
#include "lib/pack.hpp"

class Program {
public:
    void Run();

private:
    Ui m_ui;
    Editor m_editor;
    Sk::Pack m_pack;
};

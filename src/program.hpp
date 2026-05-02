#pragma once

#include "ui/ui.hpp"
#include "lib/pack.hpp"

class Program {
public:
    void Run();

private:
    Ui m_ui;
    Sk::Pack m_pack;
};

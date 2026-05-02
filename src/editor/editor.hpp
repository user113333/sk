#pragma once

#include "lib/pack.hpp"
#include "modes.hpp"

class Editor {
public:
    void Update(Sk::Pack &pack);
    void Render(Sk::Pack &pack);

    Modes& GetModes() { return modes; }

private:
    Modes modes;
};

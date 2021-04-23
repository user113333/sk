#pragma once

#include <raylib.h>

namespace camera {
    inline Camera2D camera = { { 0, 0 }, { 0, 0 }, 0, 1.0 };
    
    void update();
}

#pragma once

#include <vector>

#include "animation.hpp"
#include "background.hpp"

namespace Sk {
    struct Pack {
        std::vector<Animation> Animations;
        Background Background;
    };
}

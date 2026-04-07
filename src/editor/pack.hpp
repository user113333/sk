#pragma once

#include <vector>

#include "animation.hpp"

namespace Sk {
    struct Pack {
        std::vector<Animation> Animations;
        Background Background;
    };
}

#pragma once

#include <vec2.hpp>
#include <vec4.hpp>

namespace mouse {

    void update();

    bool is_locked();
    bool is_down();

    glm::vec2 pos();
    glm::vec2 pos_delta();
    glm::vec4 select_rect();

}

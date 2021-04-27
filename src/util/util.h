#pragma once

#include "util/camera.h"
#include "util/clipboard.h"
#include "util/mouse.h"
#include "util/fs.h"

#include <vec3.hpp>

namespace util {
    void strreverse(char* str);
    void itoa(char* str, int val);

    void rotate_y(glm::vec3* point, float rotation);
    void rotate_x(glm::vec3* point, float rotation);
}

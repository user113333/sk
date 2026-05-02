#pragma once

#include "util/camera.h"
#include "util/clipboard.h"
#include "util/mouse.h"
#include "util/fs.h"

#include <vec3.hpp>

namespace util {
    void strreverse(char* str);
    void itoa(char* str, int val);

    int strcompare(const char* str0, const char* str1);
    int strcmparr(char* str, const char** arr, int arr_count);

    void rotate_y(glm::vec3* point, float rotation);
    void rotate_x(glm::vec3* point, float rotation);
}

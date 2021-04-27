#pragma once

#include <vec3.hpp>
#include <vec4.hpp>

#include <cmath>

#include "util/util.h"

struct foreground_dest_t {
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 a_next;
    glm::vec3 b_next;

    float texture_size_x;
    float texture_size_y;
    float scale;
    float ratio;
    float delta;
    float rotation_y;
};

float foreground_calc_rotation(foreground_dest_t* dest) {
    return atan2(dest->a.y - dest->b.y, dest->a.x - dest->b.x) * RAD2DEG - 90;
}

glm::vec3 foreground_calc_dest(foreground_dest_t* dest) {
    float x = (dest->a.x - (dest->a.x - dest->b.x) * dest->ratio);
    float y = (dest->a.y - (dest->a.y - dest->b.y) * dest->ratio);
    float z = (dest->a.z - (dest->a.z - dest->b.z) * dest->ratio);

    dest->a.x = x;
    dest->a.y = y;
    dest->a.z = z;

    return { dest->a.x, dest->a.y, dest->a.z };
}

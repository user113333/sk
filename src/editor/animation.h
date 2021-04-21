#pragma once

#include <vector>
#include "vector2d.h"
#include <vec3.hpp>
#include <vec4.hpp>

class animation_t {
public:
    animation_t();
    ~animation_t();
    
    void point_push_back(glm::vec3 point);
    void point_remove(int index);
    glm::vec3* point_get(int index);
    bool point_is_selected(int index);

    void frame_push_back();
    void frame_remove(int index);

    void select();
    void move(bool all_frames);
    void move_z(bool all_frames);

    void render();
public:
    char name[50] = "New Animation";
    vector2d_t* vector;
    std::vector<int> selected;
    int selected_frame = 0;
};

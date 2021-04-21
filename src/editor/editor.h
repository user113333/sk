#pragma once

#include <raylib.h>

#include "animation.h"

namespace editor {
    void initialize();
    void update();
    void render();
    void destroy();

    void new_point();
    void new_frame();
    void new_animation();
    void delete_point(int index);
    void delete_frame(int index);
    void delete_animation(int index);

    void create_new();
    void import_file();
    void export_file();

    void select_animation(int index);
    int get_animations_selected();
    animation_t* get_animation();
    void* get_animations();
    int* get_view();
}

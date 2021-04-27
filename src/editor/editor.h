#pragma once

#include <raylib.h>

#include "animation_t.h"

namespace editor {
    void initialize();
    void update();
    void render();
    void imgui();
    void destroy();

    void new_point();
    void new_frame();
    void new_animation();
    void new_sprite();
    void delete_point(int index);
    void delete_frame(int index);
    void delete_animation(int index);

    bool file_is_open();
    void file_prepend_path(char* str);
    
    void create_new(char* str);
    void import_file(char* str);
    void export_file(char* str);
    char* get_file_open();

    void select_animation(int index);
    animation_t* get_animation();

    // VARS
    inline bool precise_select = true;
    inline int view = 1;
}

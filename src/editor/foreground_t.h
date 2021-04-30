#pragma once

#include <vector>
#include <vec3.hpp>

#include "sprite_t.h"
#include "vector2d.h"
#include "ground_t.h"

class foreground_t {
public:
    void initialize(const char* path, unsigned int x, unsigned int y);
    void add_sprite();
    void remove_sprite(int i);
    
    void render(vector2d_t* vector2d, int n, float delta, float rotation_y, float scale);
    void render_imgui(int count_m);
    void render_sprites_imgui(int count_m);

    void ground_update();
    void ground_render();
    void ground_imgui();

private:
    ground_t ground;
    std::vector<sprite_t> sprites;
    int selected = -1;
};

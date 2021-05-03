#pragma once

#include <raylib.h>
#include <vector>
#include <vec3.hpp>

#include "sprite_t.h"
#include "vector2d.h"
#include "ground_t.h"

class foreground_t {
public:
    void initialize(const char* path, unsigned int x, unsigned int y);
    void add_sprite();
    void clear_sprites();
    void add_sprite(int foreground_y, float ratio, int point_a, int point_b);
    void remove_sprite(int i);
    
    void render(vector2d_t* vector2d, int n, float delta, float rotation_y, float scale);
    void render_imgui(int count_m);
    void render_sprites_imgui(int count_m);

    void ground_update();
    void ground_render();
    void ground_imgui();

    int get_sprites_count();
    sprite_t* get_sprite(int index);
    char* get_path();
    int get_x();
    int get_y();

private:
    char path[100] = "\0";
    ground_t ground;
    std::vector<sprite_t> sprites;
    int selected = -1;

    Texture2D texture;
    float texture_size_x = 0;
    float texture_size_y = 0;
};

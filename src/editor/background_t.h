#pragma once

#include <raylib.h>
#include <vector>

struct background_texture_t {
    char path[100];
    Texture2D texture;
};

class background_t {
public:
    void next();
    void prev();
    void remove(int i);

    void load_background(char* path);
    std::vector<background_texture_t>* get_vector();

    void update();
    void render();
    void imgui();
    
private:
    int index = 0;
    float scale = 1;
    float x = 0;
    float y = 0;

    std::vector<background_texture_t> textures;

    static inline bool display = true;
};

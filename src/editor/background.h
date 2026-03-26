#pragma once

#include <string>
#include <vector>
#include <raylib.h>

class Background {
public:
    void Next();
    void Prev();
    void Update();
    void Render();
    void Imgui();
private:
    Texture2D m_texture;
    void Load(std::string path);
};

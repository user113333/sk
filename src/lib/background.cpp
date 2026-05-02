#include "background.hpp"

#include <imgui.h>
#include <raylib.h>

#include "ui/ui.h"

void Sk::Background::Next()
{

}

void Sk::Background::Prev()
{

}

void Sk::Background::Update()
{

}

void Sk::Background::Render()
{
    DrawTexture(m_texture, 0, 0, WHITE);
}

void Sk::Background::Imgui()
{
    
}

void Sk::Background::Load(std::string path)
{
    int frames;
    Image img = LoadImageAnim(path.c_str(), &frames);
    m_texture = LoadTextureFromImage(img);
}
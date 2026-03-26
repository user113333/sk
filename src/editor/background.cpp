#include "background.h"

#include <imgui.h>
#include <raylib.h>

#include "ui/ui.h"

void Background::Next()
{

}

void Background::Prev()
{

}

void Background::Update()
{

}

void Background::Render()
{
    DrawTexture(m_texture, 0, 0, WHITE);
}

void Background::Imgui()
{
    if (ImGui::BeginMenuBar()) {
        if (ImGui::MenuItem("Load new")) {
            ui::Modal.OpenFileRead("Load background: ", {"GIF files (.gif)", "*.gif"}, [this](std::string path){
                this->Load(path);
            });
        }
        ImGui::EndMenuBar();
    }
}

void Background::Load(std::string path)
{
    int frames;
    Image img = LoadImageAnim(path.c_str(), &frames);
    m_texture = LoadTextureFromImage(img);
}
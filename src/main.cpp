#include <stdio.h>

#include "imgui/imgui_layer.h"
#include "ui/editor.h"
#include "util/util.h"
#include "core.h"

void SecondUpdate()
{
    camera::Center();
}

int main(int, char**)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    InitWindow(1600, 900, "sk");
    SetExitKey(0);

    texture_point = LoadTexture(ASSETS_PATH "point.png");
    font_main = LoadFontEx(ASSETS_PATH "plex.ttf", 25, NULL, 0);

    editor::initialize();
    imgui_layer::initialize();

    int frame_count = 0;

    while (!WindowShouldClose()) {
        frame_count++;
        mouse::update();
        editor::update();
        if (frame_count == 2) {
            SecondUpdate();
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera::camera);
        editor::render();
        EndMode2D();
        imgui_layer::update();
        EndDrawing();
    }

    editor::destroy();
    imgui_layer::destroy();    
    CloseWindow();

    return 0;
}

#include <stdio.h>

#include "imgui/imgui_layer.h"
#include "editor/editor.h"
#include "util/mouse.h"
#include "util/camera.h"

Texture2D texture_point;
Font font_main;

int main(int, char**) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "sk");
    SetExitKey(0);

    texture_point = LoadTexture(ASSETS_PATH "point.png");
    font_main = LoadFontEx(ASSETS_PATH "plex.ttf", 25, NULL, 0);

    SetTargetFPS(144);

    editor::initialize();
    imgui_layer::initialize();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        camera::update();
        mouse::update();

        editor::update();
        
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

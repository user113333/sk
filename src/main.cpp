#include <raylib.h>
#include <stdio.h>

#include "imgui/imgui_layer.h"

int main(int, char**) {
    InitWindow(1600, 900, "sk");
    SetExitKey(0);
    
    imgui_layer::initialize();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        imgui_layer::update();
        EndDrawing();
    }

    imgui_layer::destroy();    
    CloseWindow();

    return 0;
}

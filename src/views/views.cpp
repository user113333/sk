#include "views.h"

#include <raylib.h>
#include <raymath.h>

#include "editor/editor.h"
#include "util/camera.h"
#include "imgui/imgui_layer.h"

void camera_update()
{
    if (imgui_layer::mouse_locked()) return;
    
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera::camera.zoom);
        camera::camera.target = Vector2Add(camera::camera.target, delta);
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera::camera);
        camera::camera.offset = GetMousePosition();
        camera::camera.target = mouseWorldPos;
        float scale = 0.2f*wheel;
        camera::camera.zoom = Clamp(expf(logf(camera::camera.zoom)+scale), 0.125f, 64.0f);
    }
}

void points_imgui() {
    editor::get_animation()->render_imgui_points();
}

void points_update() {
    editor::get_animation()->update();
}

void points_render() {
    editor::get_animation()->render_select_rect();
}

void zorder_update() {
    editor::get_animation()->zorder_update();
}

void frames_imgui() {
    editor::get_animation()->render_imgui_frames();
}

void foreground_imgui() {
    editor::get_animation()->foreground_imgui();
}

void foreground_sprites_imgui() {
    editor::get_animation()->foreground_sprites_imgui();
}

void ground_update() {
    editor::get_animation()->ground_update();
}

void ground_imgui() {
    editor::get_animation()->ground_imgui();
}

void background_update() {
    editor::get_animation()->background_update();
}

void background_imgui() {
    editor::get_animation()->background_imgui();
}

void play_imgui() {
    editor::get_animation()->play_imgui();
}

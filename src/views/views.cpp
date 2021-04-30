#include "editor/editor.h"
#include "views.h"

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

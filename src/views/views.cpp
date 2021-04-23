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

void frames_imgui() {
    editor::get_animation()->render_imgui_frames();
}

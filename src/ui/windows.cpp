#include "windows.hpp"

#include "editor.h"

void Windows::DrawImgui()
{
    editor::get_animation()->render_imgui_points();
    editor::get_animation()->render_imgui_frames();
    editor::get_animation()->foreground_imgui();
    editor::get_animation()->foreground_sprites_imgui();
    editor::get_animation()->ground_imgui();
    editor::get_animation()->background_imgui();
    editor::get_animation()->play_imgui();
}

void Windows::ImguiCheckList()
{

}

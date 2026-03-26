#pragma once

#include <imgui.h>

#include "settings.h"
#include "shortcuts.h"
#include "foreground.h"
#include "editor/editor.h"

#define VIEWS_UPDATE(X) if (views[X].update != nullptr) views[X].update()
#define VIEWS_RENDER(X) if (views[X].render != nullptr) views[X].render()
#define WINDOWS_IMGUI(X) if (windows[X].imgui != nullptr) windows[X].imgui()

struct window_t {
    const char* name;
    void (*imgui)(void);

    bool separator = false;
    bool imgui_window = true;

    int workplace_position = -1;

    int flags = 0;
};

struct view_t {
    const char* name;
    
    void (*update)(void);
    void (*render)(void);
};

void camera_update();
void points_imgui();
void points_update();
void points_render();

void zorder_update();

void frames_imgui();

void foreground_imgui();
void foreground_sprites_imgui();

void ground_update();
void ground_imgui();

void background_update();
void background_imgui();

void play_imgui();

inline window_t windows[] = {
    { "Master window", editor::imgui, false, true, 0 },
    { "Points window", points_imgui, false, true, 2 },
    { "Frames window", frames_imgui, false, true, 3 },
    { "Foreground window", foreground_imgui, false, true, 5 },
    { "Sprites window", foreground_sprites_imgui, false, true, 1 },
    { "Ground window", ground_imgui, false, false },
    { "Background window", background_imgui, false, true, -1, ImGuiWindowFlags_MenuBar },
    { "Play window", play_imgui, false, true, 4 },

    { "Settings window", settings::imgui, true, false },
    { "Shortcuts window", shortcuts::imgui, false, false }
};

inline view_t views[] {
    { "Master view", camera_update, nullptr },
    { "Points view", points_update, points_render },
    { "Z oreder view", zorder_update, points_render },
    { "Foreground view", foreground::update, nullptr },
    { "Ground view", ground_update, nullptr },
    { "Background view", background_update }
};

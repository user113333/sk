#pragma once

#include "settings.h"
#include "shortcuts.h"

#define VIEWS_UPDATE(X) if (views[X].update != nullptr) views[X].update()
#define VIEWS_RENDER(X) if (views[X].render != nullptr) views[X].render()
#define WINDOWS_IMGUI(X) if (windows[X].imgui != nullptr) windows[X].imgui()

struct window_t {
    const char* name;
    void (*imgui)(void);

    bool separator = false;
    bool imgui_window = true;
};

struct view_t {
    const char* name;
    
    void (*update)(void);
    void (*render)(void);
};

void points_imgui();
void points_update();
void points_render();
void frames_imgui();

inline window_t windows[] = {
    { "Master window", editor::imgui },
    { "Points window", points_imgui },
    { "Frames window", frames_imgui },

    { "Settings window", settings::imgui, true, false },
    { "Shortcuts window", shortcuts::imgui, false, false }
};

inline view_t views[] {
    { "Master view", nullptr, nullptr },
    { "Points view", points_update, points_render },
    { "Z oreder view", nullptr, nullptr },
    { "Foreground view", nullptr, nullptr },
    { "Ground view", nullptr, nullptr },
    { "Background view", nullptr, nullptr }
};

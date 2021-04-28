#include "ground_t.h"

#include <imgui.h>
#include <raylib.h>

#include "editor.h"
#include "util/util.h"

void ground_t::update() {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        y += mouse::pos_delta().y;
    }
}

void ground_t::render() {
    if (!display) {
        return;
    }

    float x = GetScreenWidth();
    DrawLine(-x, y, x, y, GREEN);
}

void ground_t::imgui() {
    ImGui::Checkbox("Display ground", &display);
    
    ImGui::Text("Ground: ");
    ImGui::DragFloat("Ground Y", &y, 1, -500, 500, "%.0f");
    
    ImGui::Separator();
    static float display_y = 0;
    if (ImGui::Button("Calc lowest point")) {
        display_y = editor::get_animation()->point_get_lowest();
    }
    ImGui::DragFloat("lowest point", &display_y);
}

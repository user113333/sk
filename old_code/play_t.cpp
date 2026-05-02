#include "play_t.h"

#include <imgui.h>
#include <raylib.h>

float timer = 0;

int play_t::get_frame(int cur_frame, int count) {
    if (!enabled) {
        return cur_frame;
    }

    return current_frame;
}

float play_t::get_delta(int count) {
    if (!enabled) {
        return 0;
    }

    timer += GetFrameTime();
    
    float time_scale = 1 / fps;
    if (timer > time_scale) {
        timer = timer - time_scale;
        current_frame++;
    }

    if (current_frame >= count) {
        current_frame = 0;
    }
    
    if (!smoothstep) {
        return 0;
    }

    return timer / time_scale;
}

void play_t::imgui() {
    ImGui::DragFloat("FPS", &fps, 0.1, 0.1, 100, "%0.1f");
    ImGui::Checkbox("Play", &enabled);
    ImGui::Checkbox("Smooth frame step", &smoothstep);
}

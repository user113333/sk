#pragma once

class play_t {
public:
    int get_frame(int cur_frame, int count);
    float get_delta(int count);

    void imgui();

private:
    float fps = 14;
    int current_frame = 0;
    bool enabled = false;
    bool smoothstep = true;
};

#pragma once

class ground_t {
public:
    void update();
    void render();
    void imgui();

private:
    bool display = true;
    float y = 250;
};

#pragma once

class ground_t {
public:
    void update();
    void render();
    void imgui();

public:
    float skew = 0;
    float y = 250;

private:
    bool display = false;
};

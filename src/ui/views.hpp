#pragma once

#include <string>
#include <array>

enum VIEW {
    VIEW_CAMERA = 0
};

class Views {
public:
    void Update();
    void Render();

    void ImguiRadioList();
    std::string GetActiveName();
private:
    int m_active = 0;
    const std::array<std::string, 6> m_view_names = {
        "Camera view",
        "Points view",
        "Z oreder view",
        "Foreground view",
        "Ground view",
        "Background view"
    };
};

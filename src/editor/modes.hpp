#pragma once

#include <string>
#include <vector>

enum MODE {
    MODE_CAMERA
};

class Modes {
public:
    void Update();
    void Render();

    std::vector<std::string> GetNames();
    int GetActiveIndex();
    void SetActiveIndex(int i);
    std::string GetActiveName();
private:
    int m_active = 0;
    std::vector<std::string> m_names = {
        "Camera mode",
        "Points mode",
        "Z oreder mode",
        "Foreground mode",
        "Ground mode",
        "Background mode"
    };
};

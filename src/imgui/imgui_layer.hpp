#pragma once

#include <optional>
#include <vector>
#include <string>

namespace imgui_layer {
    void Initialize();
    void Begin();
    void End();
    void Destroy();

    bool IsMouseLocked();

    std::optional<char*> DrawModalFileRead(char* modal_name, char* message, std::vector<std::string> filters);

    inline bool ImguiDemoWindowOpen = false;
}

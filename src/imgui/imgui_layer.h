#pragma once

#include "imgui_modal.h"

namespace imgui_layer {
    void Initialize();
    void Begin();
    void End();
    void Destroy();

    bool IsMouseLocked();

    inline ImGuiModal Modal;
    inline bool ImguiDemoWindowOpen = false;
}

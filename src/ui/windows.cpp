#include "windows.hpp"

#include <imgui.h>

#include "imgui/imgui_layer.h"
#include "lib/pack.hpp"

using namespace Sk;

void Windows::DrawImgui(Pack &pack)
{
    m_background_window.ImGuiWindow(pack.Background);
}

void Windows::ImguiCheckList()
{
    m_background_window.ImGuiCheckbox();

    ImGui::Separator();

    ImGui::Checkbox("Imgui Demo Window", &imgui_layer::ImguiDemoWindowOpen);
}

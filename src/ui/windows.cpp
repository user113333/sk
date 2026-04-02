#include "windows.hpp"

#include <imgui.h>

#include "editor.h"
#include "imgui/imgui_layer.h"

void Windows::DrawImgui()
{
    m_background_window.ImGuiWindow(animation_background);
}

void Windows::ImguiCheckList()
{
    m_background_window.ImGuiCheckbox();

    ImGui::Separator();

    ImGui::Checkbox("Imgui Demo Window", &imgui_layer::ImguiDemoWindowOpen);
}

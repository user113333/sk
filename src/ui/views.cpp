#include "views.hpp"

#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include "util/camera.h"
#include "imgui/imgui_layer.h"

void Views::Update()
{
    switch (m_active) {
        case VIEW_CAMERA:
            if (imgui_layer::mouse_locked()) break;
            camera::UpdateUserMouseInteraction();
            break;
    }
}

void Views::Render()
{
    
}

void Views::ImguiRadioList()
{
    for (int i = 0; i < m_view_names.size(); i++) {
        ImGui::RadioButton(m_view_names[i].c_str(), &m_active, i);
    }
}

std::string Views::GetActiveName()
{
    return m_view_names[m_active];
}
 
// void points_update() {
//     editor::get_animation()->update();
// }

// void points_render() {
//     editor::get_animation()->render_select_rect();
// }

// void zorder_update() {
//     editor::get_animation()->zorder_update();
// }

// void ground_update() {
//     editor::get_animation()->ground_update();
// }

// void background_update() {
//     editor::get_animation()->background_update();
// }

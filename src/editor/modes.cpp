#include "modes.hpp"

#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include "util/camera.h"
#include "imgui/imgui_layer.h"

#include <vector>

void Modes::Update()
{
    switch (m_active) {
        case MODE_CAMERA:
            if (imgui_layer::IsMouseLocked()) break;
            camera::UpdateUserMouseInteraction();
            break;
    }
}

void Modes::Render()
{
    
}

std::vector<std::string> Modes::GetNames()
{
    return m_names;
}

int Modes::GetActiveIndex()
{
    return m_active;
}

void Modes::SetActiveIndex(int i)
{
    m_active = i;
}

std::string Modes::GetActiveName()
{
    return m_names[m_active];
}

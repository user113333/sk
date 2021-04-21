#include "mouse.h"

#include <raylib.h>

#include "imgui/imgui_layer.h"
#include "camera.h"

namespace mouse {
    
    static glm::vec2 pressed;
    static glm::vec2 current;

    void update() {
        current.x = GetMousePosition().x;
        current.y = GetMousePosition().y;

        current.x -= camera::camera.offset.x;
        current.y -= camera::camera.offset.y;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            pressed = current;
        }
    }

    bool is_locked() {
        return imgui_layer::mouse_locked();
    }

    bool is_down() {
        return IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    }

    glm::vec2 pos() {
        return current;
    }

    glm::vec2 pos_delta() {
        return current - pressed;
    }

    glm::vec4 select_rect() {
        glm::vec2 select_size = { current.x - pressed.x, current.y - pressed.y };
        return { (select_size.x > 0 ? pressed.x : pressed.x + select_size.x), (select_size.y > 0 ? pressed.y : pressed.y + select_size.y), abs(select_size.x), abs(select_size.y)};
    }

}

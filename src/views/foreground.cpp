#include "foreground.h"

#include "util/util.h"

namespace foreground {

    void update() {
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            rotation += mouse::pos_delta().x / 100;
        }

        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            scale += mouse::scroll_delta() / 10;
        }
    }

}

#include <raylib.h>

namespace camera {

    Camera2D camera = { 0 };

    void update() {
        camera.target = (Vector2){ 0, 0 };
        camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
    }

}

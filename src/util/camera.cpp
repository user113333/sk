#include "camera.h"

#include <raylib.h>
#include <raymath.h>

namespace camera {

    void UpdateUserMouseInteraction()
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera::camera.zoom);
            camera::camera.target = Vector2Add(camera::camera.target, delta);
        }

        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera::camera);
            camera::camera.offset = GetMousePosition();
            camera::camera.target = mouseWorldPos;
            float scale = 0.2f*wheel;
            camera::camera.zoom = Clamp(expf(logf(camera::camera.zoom)+scale), 0.125f, 64.0f);
        }    
    }

    void Center()
    {
        camera.target.x = -(GetScreenWidth() / 2);
        camera.target.y = -(GetScreenHeight() / 2);
        camera.offset = { 0, 0 };
        camera.zoom = 1;
        camera.rotation = 0;
    }

}

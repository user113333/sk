#include "camera.h"

namespace camera {

    void update() {
        
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

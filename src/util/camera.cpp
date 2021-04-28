#include "camera.h"

namespace camera {

    void update() {
        camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    }

}

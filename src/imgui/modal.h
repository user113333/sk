#pragma once

namespace modal {
    void open(const char* message, const char* default_input, void (*callback)(char*));
    void open(const char* message, void (*callback)(void));
    void update();
}

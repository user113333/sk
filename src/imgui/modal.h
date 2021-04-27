#pragma once

enum MODAL_TYPE {
    MODAL_TYPE_MESSAGE = 0b000000001,
    MODAL_TYPE_INPUT = 0b000000010,
    MODAL_TYPE_FILE_OPEN = 0b000000100,
    MODAL_TYPE_FILE_SAVE = 0b000001000,

    MODAL_OPEN = 0b100000000,
    MODAL_OPEN_INVERTED = 0b011111111
};

namespace modal {
    void open(const char* message, const char* default_input, void (*callback_func)(char*), MODAL_TYPE type);
    void update();
}

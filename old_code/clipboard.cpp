#include <cstring>

#define ARRAY_SIZE 2000

namespace clipboard {
    static char clip_data[ARRAY_SIZE];

    void set(char* str, int length) {
        if (length > ARRAY_SIZE) {
            length = ARRAY_SIZE;
        }
        
        memcpy(clip_data, str, length);
    }

    char* get() {
        return clip_data;
    }
}

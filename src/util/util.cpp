#include <cstring>

#include <vec3.hpp>
#include <cmath>

namespace util {

    void strreverse(char* str) {
        int len = strlen(str) - 1;
        char ch;

        for (int i = 0; i <= len / 2; i++) {
            ch = str[i];
            str[i] = str[len-i];
            str[len-i] = ch;
        }
    }

    void itoa(char* str, int val) {
        int sign = 0;
        int i = 0;

        if (val < 0) {
            val = -val;
            sign = 1;
        }

        do {
            str[i++] = val % 10 + '0';
        } while ((val /= 10) > 0);

        if (sign) {
            str[i++] = '-';
        }

        str[i++] = '\0';
        strreverse(str);
    }

    void rotate_y(glm::vec3* point, float rotation) {
        point->x = point->x * cos(rotation) + point->z * sin(rotation);
        point->y = point->y;
        point->z = -point->x * sin(rotation) + point->z * cos(rotation);
    }

    void rotate_x(glm::vec3* point, float rotation) {
        point->x = point->x;
        point->y = point->y * cos(rotation) - point->z * sin(rotation);
        point->z = point->y * sin(rotation) + point->z * cos(rotation);
    }

}

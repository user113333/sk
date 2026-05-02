#include "vector2d.h"

#include <stdlib.h>
#include <string.h>

struct vector2d_t* vector2d_create(int item_size, int m, int n) {
    struct vector2d_t* vector2d = (vector2d_t*)malloc(sizeof(struct vector2d_t));

    vector2d->data = calloc(m * n, item_size);
    vector2d->length_m = m;
    vector2d->length_n = n;
    vector2d->count_m = 0;
    vector2d->count_n = 0;
    vector2d->item_size = item_size;

    return vector2d;
}

void* vector2d_get(struct vector2d_t* vector2d, int m, int n) {
    return ((char*)vector2d->data) + ((vector2d->length_m * n) + m) * vector2d->item_size;
}

void vector2d_push_back_m(struct vector2d_t* vector2d, void* data) {
    for (int i = 0; i < vector2d->count_n; i++) {
        memcpy(vector2d_get(vector2d, vector2d->count_m, i), data, vector2d->item_size);
    }

    vector2d->count_m++;
}

void vector2d_push_back_n(struct vector2d_t* vector2d, void* data) {
    for (int i = 0; i < vector2d->count_m; i++) {
        memcpy(vector2d_get(vector2d, i, vector2d->count_n), data, vector2d->item_size);
    }

    vector2d->count_n++;
}

void vector2d_remove_m(struct vector2d_t* vector2d, int index) {
    for (int i = 0; i < vector2d->count_n; i++) {
        memcpy(vector2d_get(vector2d, index, i), vector2d_get(vector2d, index + 1, i), (vector2d->length_m - (index + 1)) * vector2d->item_size);
    }

    vector2d->count_m--;
}

void vector2d_remove_n(struct vector2d_t* vector2d, int index) {
    memcpy(vector2d_get(vector2d, 0, index), vector2d_get(vector2d, 0, index + 1), (vector2d->count_n - (index + 1)) * vector2d->item_size * vector2d->length_m);

    vector2d->count_n--;
}

void vector2d_pop_m(struct vector2d_t* vector2d) {
    vector2d_remove_m(vector2d, vector2d->count_m - 1);
}

void vector2d_pop_n(struct vector2d_t* vector2d) {
    vector2d_remove_n(vector2d, vector2d->count_n - 1);
}

void vector2d_clear(struct vector2d_t* vector2d) {
    vector2d->count_m = 0;
    vector2d->count_n = 0;
}

void vector2d_free(struct vector2d_t* vector2d) {
    vector2d = 0;
    vector2d->count_n = 0;
    free(vector2d->data);
    free(vector2d);
}

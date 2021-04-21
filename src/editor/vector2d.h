#ifndef VECTOR2D_H
#define VECTOR2D_H

struct vector2d_t {
    void* data;
    int count_m;
    int count_n;
    int length_m;
    int length_n;
    int item_size;
};

struct vector2d_t* vector2d_create(int item_size, int m, int n);

void* vector2d_get(struct vector2d_t* vector2d, int m, int n);
void vector2d_push_back_m(struct vector2d_t* vector2d, void* data);
void vector2d_push_back_n(struct vector2d_t* vector2d, void* data);
void vector2d_remove_m(struct vector2d_t* vector2d, int index);
void vector2d_remove_n(struct vector2d_t* vector2d, int index);
void vector2d_pop_m(struct vector2d_t* vector2d);
void vector2d_pop_n(struct vector2d_t* vector2d);
void vector2d_clear(struct vector2d_t* vector2d);
void vector2d_free(struct vector2d_t* vector);

#endif // VECTOR2D_H

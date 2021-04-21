#include "animation.h"

#include <cstring>

#include "editor.h"
#include "util/util.h"
#include "core.h"
#include "util/mouse.h"

animation_t::animation_t() {
    vector = vector2d_create(sizeof(glm::vec3), 100, 100);
    frame_push_back();
}

animation_t::~animation_t() {
    vector2d_free(vector);
}

void animation_t::point_push_back(glm::vec3 point) {
    vector2d_push_back_m(vector, &point);
}

void animation_t::point_remove(int index) {
    vector2d_remove_m(vector, index);
}

glm::vec3* animation_t::point_get(int index) {
    return (glm::vec3*)vector2d_get(vector, index, selected_frame);
}

bool animation_t::point_is_selected(int index) {
    for (int i = 0; i < selected.size(); i++) {
        if (index == selected[i]) {
            return true;
        }
    }

    return false;
}

void animation_t::frame_push_back() {
    glm::vec3 temp_point = { 0, 0, 0 };
    vector2d_push_back_n(vector, &temp_point);
    
    if (vector->count_n < 2) {
        return;
    }

    for (int i = 0; i < vector->count_m; i++) {
        glm::vec3* point1 = (glm::vec3*)vector2d_get(vector, i, vector->count_n - 1);
        glm::vec3* point2 = (glm::vec3*)vector2d_get(vector, i, vector->count_n - 2);
        memcpy(point1, point2, vector->item_size);
    }
}

void animation_t::frame_remove(int index) {
    vector2d_remove_n(vector, index);
}

void animation_t::select() {
    glm::vec4 select = mouse::select_rect();
    
    // INFO: Makes point bounds bigger
    // select.x -= editor::texture_point.width / 2;
    // select.y -= editor::texture_point.height / 2;
    // select.z += editor::texture_point.width;
    // select.w += editor::texture_point.height;

    if (!IsKeyDown(KEY_LEFT_SHIFT)) {
        selected.clear();
    }

    for (int i = 0; i < vector->count_m; i++) {
        glm::vec3* point = point_get(i);
        if (point->x > select.x && point->x < select.x + select.z && point->y > select.y && point->y < select.y + select.w) {
            selected.push_back(i);
        }
    }
}

void animation_t::move(bool all_frames) {
    static glm::vec2 select_rect_left = { 0, 0 };
    glm::vec2 select_rect = mouse::pos_delta();
    if (select_rect.x == 0 && select_rect.y == 0) {
        select_rect_left.x = 0;
        select_rect_left.y = 0;
    }

    for (int i = 0; i < selected.size(); i++) {
        if (all_frames) {
            for (int n = 0; n < vector->count_n; n++) {
                glm::vec3* point = (glm::vec3*) vector2d_get(vector, selected[i], n);
                point->x += select_rect.x - select_rect_left.x;
                point->y += select_rect.y - select_rect_left.y;
            }
        } else {
            glm::vec3* point = (glm::vec3*) vector2d_get(vector, selected[i], selected_frame);
            point->x += select_rect.x - select_rect_left.x;
            point->y += select_rect.y - select_rect_left.y;
        }
    }
    
    select_rect_left.x = select_rect.x;
    select_rect_left.y = select_rect.y;
}

void animation_t::move_z(bool all_frames) {
}

void animation_t::render() {
    char str[10];

    for (int i = 0; i < vector->count_m; i++) {
        util::itoa(str, i);
        glm::vec3* point = point_get(i);
        DrawTexture(texture_point, point->x - texture_point.width / 2, point->y - texture_point.height / 2, point_is_selected(i) ? COLOR_PRIMARY : COLOR_WHITE);
        DrawTextEx(font_main, str, { point->x + texture_point.width / 2, point->y - 5 - texture_point.height / 2 }, font_main.baseSize, 0, COLOR_WHITE);
    }
}

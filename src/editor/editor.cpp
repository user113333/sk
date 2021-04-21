#include "editor.h"

#include <raylib.h>
#include <vec3.hpp>

#include <vector>
#include <cstring>

#include "core.h"
#include "util/mouse.h"
#include "views/views.h"

namespace editor {

    static std::vector<animation_t*> animations;
    static int animations_selected = 0;
    static int view = 0;

    void initialize() {
        new_animation();
    }

    void update() {
        char str[50];
        strcpy(str, "sk - ");
        strcat(str, get_animation()->name);
        SetWindowTitle(str);

        switch (view) {
            case MASTER_ID:
                master::update();
            break;

            case POINTS_ID:
                points::update();
            break;
        }
    }

    void render() {
        // Render points
        animations[animations_selected]->render();

        switch (view) {
            case MASTER_ID:
                master::render();
            break;

            case POINTS_ID:
                points::render();
            break;
        }

        // Render center
        DrawRectangle(-2, -8, 4, 16, COLOR_WHITE50);
        DrawRectangle(-8, -2, 16, 4, COLOR_WHITE50);
    }

    void destroy() {
        // TODO:
    }

    void new_point() {
        animations[animations_selected]->point_push_back({ 0, 0, 0 });
    }

    void new_frame() {
        animations[animations_selected]->frame_push_back();
    }

    void new_animation() {
        animations_selected = animations.size();
        animations.push_back(new animation_t);
    }

    void delete_point(int index) {
        animations[animations_selected]->point_remove(index);
    }

    void delete_frame(int index) {
        animations[animations_selected]->frame_remove(index);
    }

    void delete_animation(int index) {
        animations.erase(animations.begin() + index);

        if (animations.size() == 0) {
            new_animation();
        }
    }

    void create_new() {
        animations.empty();
        new_animation();
    }

    void import_file() {
    }

    void export_file() {
    }

    void select_animation(int index) {
        animations_selected = index;
    }

    int get_animations_selected() {
        return animations_selected;
    }

    animation_t* get_animation() {
        return animations[animations_selected];
    }

    void* get_animations() {
        return &animations;
    }

    int* get_view() {
        return &view;
    }

}

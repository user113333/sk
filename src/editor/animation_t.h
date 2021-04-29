#pragma once

#include <vector>
#include "vector2d.h"
#include <vec3.hpp>
#include <vec4.hpp>
#include "foreground_t.h"
#include "ground_t.h"
#include "background_t.h"

#define ANIMATION_NAME_LENGTH 50

inline bool animation_all_frames;

class animation_t {
public:
    animation_t();
    ~animation_t();
    char* get_name();
    
    void point_push_back(glm::vec3 point);
    void point_remove(int index);
    glm::vec3* point_get(int index);
    int point_count();
    float point_get_lowest();

    void frame_push_back();
    void frame_remove(int index);
    void frame_pop();
    int frame_count();

    void selection_select();
    void selection_remove(int i);
    void selection_push_back(int val);
    void selection_delete();
    void selection_empty();
    void selection_all();
    bool selection_contains(int index);
    bool selection_is_empty();
    int selection_size();

    void foreground_push_back();
    void foreground_load(const char* foreground_path, unsigned int x, unsigned int y);
    void foreground_render();
    void foreground_imgui();
    void foreground_sprites_imgui();

    void ground_update();
    void ground_render();
    void ground_imgui();

    void background_update();
    void background_render();
    void background_imgui();
    void background_load(char* path);

    void update();
    private:
    void update_select();
    void update_move(bool all_frames);
    void update_move_z(bool all_frames);
    public:
    void render_points();
    void render_select_rect();
    void render_imgui_points();
    void render_imgui_frames();

    void clipboard_copy();
    void clipboard_paste();

private:
    char name[ANIMATION_NAME_LENGTH] = "New Animation";
    vector2d_t* vector;
    std::vector<int> selection;
    int current_frame = 0;
    static inline foreground_t foreground;
    static inline ground_t ground;
    static inline background_t background;
};

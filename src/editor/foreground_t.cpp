#include "foreground_t.h"

#include <raylib.h>
#include <imgui.h>

#include <cstring>
#include <cmath>
#include <stdio.h>

#include "editor.h"
#include "util/util.h"
#include "foreground_dest.h"
#include "views/foreground.h"

static foreground_dest_t dest;

static char foreground_path[50] = "res/test.png";

void foreground_t::initialize(const char* path, unsigned int x, unsigned int y) {
    char str[100];
    strcpy(str, path);
    editor::file_prepend_path(str);

    texture_size_x = x;
    texture_size_y = y;

    texture = LoadTexture(str);

    if (texture.id != 0) {
        strcpy(this->path, path);
    } else {
        strcpy(this->path, "\0");
    }

    dest.texture_size_x = x;
    dest.texture_size_y = y;

    if (path != foreground_path) {
        strcpy(foreground_path, path);
    }
}

void foreground_t::add_sprite() {
    sprite_t sprite;
    sprites.push_back(sprite);
}

void foreground_t::add_sprite(int foreground_y, float ratio, int point_a, int point_b) {
    sprite_t sprite;

    sprite.foreground_y = foreground_y;
    sprite.ratio = ratio;
    sprite.point_a = point_a;
    sprite.point_b = point_b;
    
    sprites.push_back(sprite);
}

void foreground_t::clear_sprites() {
    sprites.clear();
}

void foreground_t::remove_sprite(int i) {
    sprites.erase(sprites.begin() + i);
}

void foreground_t::render(vector2d_t* vector2d, int n, float delta, float rotation_y, float scale) {
    if (!foreground::display) {
        return;
    }

    float src_x = 0;
    float src_y = 0;
    float src_width = texture_size_x;
    float src_height = texture_size_y;
    float dest_width = src_width * scale;
    float dest_height = src_height * scale;
    int n_next = n + 1;

    if (vector2d->count_n == n_next) {
        n_next = 0;
    }

    dest.delta = delta;
    dest.rotation_y = rotation_y;
    dest.scale = scale;

    for (int i = 0; i < sprites.size(); i++) {
        src_y = sprites[i].foreground_y * texture_size_y;
        dest_height = src_height * scale;

        Color c = Color{200, 255, 0, 255};
        if (!window_sprites_focused || i != window_sprites_selected) {
            c = WHITE;
        }
        
        dest.ratio = sprites[i].ratio;
        dest.a = *(glm::vec3*)vector2d_get(vector2d, sprites[i].point_a, n);
        dest.b = *(glm::vec3*)vector2d_get(vector2d, sprites[i].point_b, n);
        dest.a_next = *(glm::vec3*)vector2d_get(vector2d, sprites[i].point_a, n_next);
        dest.b_next = *(glm::vec3*)vector2d_get(vector2d, sprites[i].point_b, n_next);

        // TODO: ground?
        // dest.a -= ground.y;
        // dest.b -= ground.y;
        // util::rotate_x(&dest.a, ground.skew);
        // util::rotate_x(&dest.b, ground.skew);
        // dest.a += ground.y;
        // dest.b += ground.y;

        util::rotate_y(&dest.a, dest.rotation_y);
        util::rotate_y(&dest.b, dest.rotation_y);
        util::rotate_y(&dest.a_next, dest.rotation_y);
        util::rotate_y(&dest.b_next, dest.rotation_y);

        // smooth play
        glm::vec2 dest_a = (dest.a_next - dest.a) * dest.delta + dest.a;
        glm::vec2 dest_b = (dest.b_next - dest.b) * dest.delta + dest.b;

        glm::vec3 p = foreground_calc_dest(&dest);

        // TODO: ratio - scale interferance
        float hypot = hypotf(dest_a.x - dest_b.x, dest_a.y - dest_b.y);
        if (sprites[i].point_a != sprites[i].point_b && (src_height * scale > hypot)) {
            dest_height = hypot;
        }

        DrawTexturePro(
            texture,
            { src_x, src_y, src_width, src_height },
            { p.x, p.y, dest_width, dest_height },
            { dest_width / 2, dest_height / 2 },
            sprites[i].point_a == sprites[i].point_b ? 0 : foreground_calc_rotation(&dest),
            c
        );
    }
}

void foreground_t::render_imgui(int count_m) {
    static char str_path[100];
    static int sprite_width = 16;
    static int sprite_height = 16;
    
    ImGui::Text("Foreground: ");
    ImGui::DragFloat("scale", &foreground::scale, 0.01, 0, 100, "%0.2f");
    ImGui::DragFloat("rotation", &foreground::rotation, 0.02, 0, 0, "%0.2f");
    ImGui::Separator();
    ImGui::Text("Load Foreground");
    ImGui::InputText("\".png\" File path", foreground_path, IM_ARRAYSIZE(foreground_path));

    if (IsKeyPressed(KEY_ENTER) && ImGui::IsItemFocused()) {
        initialize(foreground_path, sprite_width, sprite_height);
    }

    if (editor::file_is_open()) {
        static ImVec4 col = { 255, 255, 255, 255 };
        strcpy(str_path, foreground_path);
        editor::file_prepend_path(str_path);
        
        if (ImGui::IsItemFocused()) {
            if (!fs::is_directory(str_path) && fs::is_file(str_path))
                col = { 0, 255, 0, 255 };
            else
                col = { 255, 0, 0, 255 };
        }
            
        ImGui::TextColored(col, "%s", str_path);
    } else {
        ImGui::TextColored({ 255, 0, 0, 255 }, "%s -> relative to exe", foreground_path);
    }
    
    ImGui::DragInt("Sprite width", &sprite_width, 1, 0, INT16_MAX);
    ImGui::DragInt("Sprite height", &sprite_height, 1, 0, INT16_MAX);

    if (ImGui::Button("Load foreground [Enter]")) {
        initialize(foreground_path, sprite_width, sprite_height);
    }

    if (texture.id == 0) {
        return;
    }

    float zoom = 2;
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
    ImGui::Image((void*)texture.id, { texture.width * zoom, texture.height * zoom }, uv_min, uv_max, tint_col, border_col);
    if (ImGui::IsItemHovered()) {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::BeginTooltip();
        float region_sz = 32.0f;
        float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
        float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
        float zoom_tooltip = 4.0f * zoom;
        if (region_x < 0.0f) { region_x = 0.0f; }
        else if (region_x > texture.width - region_sz) { region_x = texture.width - region_sz; }
        if (region_y < 0.0f) { region_y = 0.0f; }
        else if (region_y > texture.height - region_sz) { region_y = texture.height - region_sz; }
        ImGui::Text("Min: (%.0f, %.0f)", region_x, region_y);
        ImGui::Text("Max: (%.0f, %.0f)", region_x + region_sz, region_y + region_sz);
        ImVec2 uv0 = ImVec2((region_x) / texture.width, (region_y) / texture.height);
        ImVec2 uv1 = ImVec2((region_x + region_sz) / texture.width, (region_y + region_sz) / texture.height);
        ImGui::Image((void*)texture.id, ImVec2(region_sz * zoom_tooltip, region_sz * zoom_tooltip), uv0, uv1, tint_col, border_col);
        ImGui::EndTooltip();
    }

    if (window_sprites_selected < 0 || !window_sprites_focused) {
        return;
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImVec2 p0 = ImGui::GetWindowContentRegionMin();
	ImVec2 p1 = ImGui::GetWindowContentRegionMax();
    p0.x += ImGui::GetWindowPos().x;
    p0.y += ImGui::GetWindowPos().y;
    p1.x += ImGui::GetWindowPos().x;
    p1.y += ImGui::GetWindowPos().y;

    // draw_list->PushClipRect(p0, p1);

    p0 = ImGui::GetItemRectMin();
    p1 = ImGui::GetItemRectMax();
    
    p0.y += sprites[window_sprites_selected].foreground_y * texture_size_y * zoom;
    p1.y = p0.y + texture_size_y * zoom;
    
    draw_list->AddRect(p0, p1, IM_COL32(200, 255, 0, 255), 0, 0, 2);

    p1.x = p0.x + texture_size_x * zoom;
    draw_list->AddRect(p0, p1, IM_COL32(200, 255, 0, 255), 0, 0, 2);
    
    // draw_list->PopClipRect();
}

void foreground_t::render_sprites_imgui(int count_m) {
    window_sprites_focused = ImGui::IsWindowFocused() || ImGui::IsAnyItemFocused();
    static char str[10];

    ImGui::Checkbox("Display sprites", &foreground::display);

    ImGui::Text("Sprites: ");
    if (ImGui::BeginListBox("Sprites", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (int i = 0; i < sprites.size(); i++) {
            sprite_t sprite = sprites.at(i);
            bool is_selected = window_sprites_selected == i;
            
            util::itoa(str, i);

            if (ImGui::Selectable(str, is_selected) || (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))) {
                window_sprites_selected = i;
            }

            window_sprites_focused |= ImGui::IsItemFocused();

            if (ImGui::BeginPopupContextItem()) {
                ImGui::Text("sprite(y: %d, ratio: %d, a: %d, b: %d)", sprite.foreground_y, sprite.ratio, sprite.point_a, sprite.point_b);
                ImGui::Separator();

                if (ImGui::Button("Delete")) {
                    remove_sprite(i);
                    if (window_sprites_selected >= sprites.size()) {
                        window_sprites_selected = sprites.size() - 1;
                    }

                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    if (ImGui::Button("Add sprite")) {
        add_sprite();
    }

    ImGui::Text("Selected sprite[%d]: ", window_sprites_selected);
    
    if (window_sprites_selected < 0) {
        return;
    }

    sprite_t& sprite = sprites.at(window_sprites_selected);
    ImGui::SliderInt("foreground_y", &sprite.foreground_y, 0, texture.height == 0 ? 0 : texture.height / texture_size_y - 1);
    ImGui::SliderFloat("ratio", &sprite.ratio, 0, 1);
    ImGui::SliderInt("point_a", &sprite.point_a, 0, count_m == 0 ? 0 : count_m - 1);
    ImGui::SliderInt("point_b", &sprite.point_b, 0, count_m == 0 ? 0 : count_m - 1);
}

void foreground_t::ground_update() {
    ground.update();
}

void foreground_t::ground_render() {
    ground.render();
}

void foreground_t::ground_imgui() {
    ground.imgui();
}

int foreground_t::get_sprites_count() {
    return sprites.size();
}

sprite_t* foreground_t::get_sprite(int index) {
    return &sprites[index];
}

char* foreground_t::get_path() {
    return path;
}

int foreground_t::get_x() {
    return texture_size_x;
}

int foreground_t::get_y() {
    return texture_size_y;
}

#include "foreground_t.h"

#include <raylib.h>
#include <imgui.h>

#include "editor.h"
#include "util/util.h"
#include "foreground_dest.h"

static Texture2D texture;
static float texture_size_x = 0;
static float texture_size_y = 0;
static foreground_dest_t dest;

void foreground_t::initialize(const char* path, unsigned int x, unsigned int y) {
    texture_size_x = x;
    texture_size_y = y;

    texture = LoadTexture(path);

    dest.texture_size_x = x;
    dest.texture_size_y = y;
}

void foreground_t::add_sprite() {
    sprite_t sprite;
    sprites.push_back(sprite);
}

void foreground_t::render(vector2d_t* vector2d, int n, float delta, float rotation_y, float scale) {
    float src_x = texture.width / texture_size_x;
    float src_y = 0;
    int n_next = n + 1;

    if (vector2d->count_n == n_next) {
        n_next = 0;
    }

    dest.delta = 0;
    dest.rotation_y = rotation_y;
    dest.scale = scale;

    for (int i = 0; i < sprites.size(); i++) {
        src_y = sprites[i].foreground_y * texture_size_y;
        
        dest.ratio = sprites[i].ratio;
        dest.a = *(glm::vec3*)vector2d_get(vector2d, sprites[i].point_a, n);
        dest.b = *(glm::vec3*)vector2d_get(vector2d, sprites[i].point_b, n);
        dest.a_next = *(glm::vec3*)vector2d_get(vector2d, sprites[i].point_a, n_next);
        dest.b_next = *(glm::vec3*)vector2d_get(vector2d, sprites[i].point_b, n_next);

        glm::vec3 p = foreground_calc_dest(&dest);

        DrawTextureTiled(
            texture,
            { src_x, src_y, texture_size_x, texture_size_x },
            { p.x, p.y, texture_size_x, texture_size_y },
            { texture_size_x / 2, texture_size_y / 2 },
            foreground_calc_rotation(&dest),
            1.0,
            WHITE
        );
    }
}

static int selected = -1;
void foreground_t::render_imgui(int count_m) {
    // static char str[50] = "foreground.png";
    static char str[50] = "res/point.png";
    static int sprite_width = 16;
    static int sprite_height = 16;
    
    ImGui::InputText("\".png\" File path", str, IM_ARRAYSIZE(str));
    ImGui::DragInt("Sprite width", &sprite_width, 1, 0, INT_MAX);
    ImGui::DragInt("Sprite height", &sprite_height, 1, 0, INT_MAX);

    if (ImGui::Button("Load foreground [Enter]") || (IsKeyPressed(KEY_ENTER) && ImGui::IsWindowFocused())) {
        initialize(str, sprite_width, sprite_height);
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

    if (selected < 0) {
        return;
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImVec2 p0 = ImGui::GetWindowContentRegionMin();
	ImVec2 p1 = ImGui::GetWindowContentRegionMax();
    p0.x += ImGui::GetWindowPos().x;
    p0.y += ImGui::GetWindowPos().y;
    p1.x += ImGui::GetWindowPos().x;
    p1.y += ImGui::GetWindowPos().y;

    draw_list->PushClipRect(p0, p1);

    p0 = ImGui::GetItemRectMin();
    p1 = ImGui::GetItemRectMax();
    
    p0.y += sprites[selected].foreground_y * texture_size_y * zoom;
    p1.y = p0.y + texture_size_y * zoom;
    
    draw_list->AddRect(p0, p1, IM_COL32(200, 255, 0, 255), 0, 0, 2);

    p1.x = p0.x + texture_size_x * zoom;
    draw_list->AddRect(p0, p1, IM_COL32(200, 255, 0, 255), 0, 0, 2);
    
    draw_list->PopClipRect();
}

void foreground_t::render_sprites_imgui(int count_m) {
    static char str[10];

    ImGui::Text("Sprites: ");
    if (ImGui::BeginListBox("Sprites", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (int i = 0; i < sprites.size(); i++) {
            sprite_t sprite = sprites.at(i);
            bool is_selected = selected == i;
            
            util::itoa(str, i);

            if (ImGui::Selectable(str, is_selected) || (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))) {
                selected = i;
            }

            if (ImGui::BeginPopupContextItem()) {
                ImGui::Text("sprite(y: %d, ratio: %d, a: %d, b: %d)", sprite.foreground_y, sprite.ratio, sprite.point_a, sprite.point_b);
                ImGui::Separator();

                if (ImGui::Button("Delete")) {
                    sprites.erase(sprites.begin() + i);
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    ImGui::Text("Selected sprite[%d]: ", selected);
    
    if (selected < 0) {
        return;
    }

    sprite_t& sprite = sprites.at(selected);
    ImGui::SliderInt("foreground_y", &sprite.foreground_y, 0, texture.width == 0 ? 0 : texture.width / texture_size_x - 1);
    ImGui::SliderFloat("ratio (-1 = static)", &sprite.ratio, 0, 1);
    ImGui::SliderInt("point_a", &sprite.point_a, 0, count_m == 0 ? 0 : count_m - 1);
    ImGui::SliderInt("point_b", &sprite.point_b, 0, count_m == 0 ? 0 : count_m - 1);
}

#include "background_t.h"

#include <imgui.h>

#include <algorithm>

#include "editor.h"
#include "util/util.h"
#include "imgui/modal.h"

const char* image_extensions[] = {
    "png",
    "gif",
    "jpg"
};

void background_t::next() {
    index++;

    if (index >= textures.size()); {
        index = 0;
    }
}

void background_t::prev() {
    index--;

    if (index < 0) {
        index = textures.size() - 1;
    }
}

void background_t::remove(int i) {
    textures.erase(textures.begin() + i);

    if (index >= textures.size()); {
        index = textures.size() - 1;
    }
}

void background_t::load_background(char* path) {
    textures.clear();
    index = 0;

    int count;
    char** files = GetDirectoryFiles(path, &count);

    for (int i = 0; i < count; i++) {
        char* file_name = files[i];

        if (!util::strcmparr(strstr(file_name, ".") + 1, image_extensions, IM_ARRAYSIZE(image_extensions))) {
            continue;
        }

        background_texture_t bt;

        strcpy(bt.path, path);

        if (path[strlen(path) - 1] != '/') {
            strcat(bt.path, "/");
        }

        strcat(bt.path, file_name);
        editor::file_prepend_path(bt.path);

        Texture2D texture = LoadTexture(bt.path);

        strcpy(bt.path, file_name);

        if (texture.id == 0) {
            continue;
        }

        bt.texture = texture;
        textures.push_back(bt);
    }

    struct {
        bool operator()(background_texture_t a, background_texture_t b) const { return strcmp(a.path, b.path) < 0; }
    } custom_less;
    std::sort(textures.begin(), textures.end(), custom_less);
}

std::vector<background_texture_t>* background_t::get_vector() {
    return &textures;
}

void background_t::update() {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        x += mouse::pos_delta().x;
        y += mouse::pos_delta().y;
    }

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        scale += mouse::scroll_delta() / 2;
    }
}

void background_t::render() {
    if (textures.size() == 0 || !display) {
        return;
    }

    Texture2D texture = textures[index].texture;
    DrawTextureEx(texture, { x - texture.width / 2 * scale, y - texture.height / 2 * scale }, 0, scale, WHITE);
}

void background_t::imgui() {
    if (ImGui::Button("Load Background")) {
        modal::open("Locate the directory that contains the background images", "background", editor::background_load, MODAL_TYPE_DIRECTORY_OPEN);
    }
    
    ImGui::Checkbox("Display background", &display);
    ImGui::Text("Background: ");
    ImGui::DragFloat("scale", &scale, 0.01, 0, 100, "%0.2f");
    ImGui::DragFloat("x", &x, 1, 0, 0, "%0.0f");
    ImGui::DragFloat("y", &y, 1, 0, 0, "%0.0f");
    
    ImGui::Separator();

    static char str[50];
    if (ImGui::BeginListBox("Backgrounds", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (int i = 0; i < textures.size(); i++) {
            background_texture_t bt = textures[i];
            bool is_selected = i == index;
            
            util::itoa(str, i);
            strcat(str, ": ");
            strcat(str, bt.path);

            if (ImGui::Selectable(str, is_selected) || (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))) {
                index = i;
            }

            // Drag api
            if (ImGui::IsItemActive() && !ImGui::IsItemHovered()) {
                int i_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                if (i_next >= 0 && i_next < textures.size()) {
                    textures[i] = textures[i_next];
                    textures[i_next] = bt;
                    ImGui::ResetMouseDragDelta();
                    index = i_next;
                }
            }

            if (ImGui::BeginPopupContextItem()) {
                ImGui::Text("%s", bt.path);

                if (ImGui::Button("Delete")) {
                    remove(i);
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
    if (ImGui::BeginTable("frames", 4)) {
        for (int i = 0; i < textures.size(); i++) {
            if (i % 4 == 0) {
                ImGui::TableNextRow();
            }

            ImGui::TableNextColumn();

            if (i == index) {
                strcpy(str, "--");
                util::itoa(str + strlen(str), i);
                strcat(str, "--");
            } else {
                util::itoa(str, i);
            }

            if (ImGui::Button(str, { -1, 0 })) {
                index = i;
            }
        }
        ImGui::EndTable();
    }
}

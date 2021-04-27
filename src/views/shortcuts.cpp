#include <raylib.h>
#include <imgui.h>

#include "editor/editor.h"
#include "ui/ui.h"
#include "imgui/modal.h"
#include "views/views.h"

#define PRESSED(X) IsKeyPressed(X)

namespace shortcuts {

    void update() {
        for (int i = 0; i < 8; i++) {
            if (PRESSED(KEY_ONE + i)) {
                if (i >= IM_ARRAYSIZE(views)) {
                    continue;
                }
                
                editor::view = i;
            }
        }

        if (PRESSED(KEY_GRAVE)) {
            ui::show_imgui = !ui::show_imgui;
        }

        // ===== CONTROL SHORTCUTS =====
        if (!IsKeyDown(KEY_LEFT_CONTROL)) {
            return;
        }

        if (PRESSED(KEY_SPACE)) {
            editor::new_point();
        }

        if (PRESSED(KEY_DELETE)) {
            editor::get_animation()->selection_delete();
        }

        if (PRESSED(KEY_C)) {
            editor::get_animation()->clipboard_copy();
        }

        if (PRESSED(KEY_V)) {
            editor::get_animation()->clipboard_paste();
        }

        if (PRESSED(KEY_O)) {
            modal::open("Import file path: ", "out", editor::import_file, MODAL_TYPE_FILE_OPEN);
        }

        if (PRESSED(KEY_S)) {
            if (editor::get_file_open()[0] == '\0') {
                modal::open("Export file path: ", "out", editor::export_file, MODAL_TYPE_FILE_SAVE);
            }
        }
    }

    void imgui() {
        ImGui::Text("Shortcuts: ");
    }

}

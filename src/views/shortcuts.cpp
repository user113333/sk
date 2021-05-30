#include <raylib.h>
#include <imgui.h>

#include "editor/editor.h"
#include "ui/ui.h"
#include "imgui/modal.h"
#include "views/views.h"
#include "editor/background_t.h"

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

        if ((!IsKeyDown(KEY_LEFT_CONTROL) || editor::bg_with_frames) && PRESSED(KEY_Q)) {
            editor::get_animation()->background_prev();
        }

        if ((!IsKeyDown(KEY_LEFT_CONTROL) || editor::bg_with_frames) && PRESSED(KEY_E)) {
            editor::get_animation()->background_next();
        }

        if (PRESSED(KEY_UP)) {
            editor::get_animation()->selection_change(0, 1);
        }
        
        if (PRESSED(KEY_DOWN)) {
            editor::get_animation()->selection_change(0, -1);
        }

        if (PRESSED(KEY_LEFT)) {
            editor::get_animation()->selection_change(-1, 0);
        }

        if (PRESSED(KEY_RIGHT)) {
            editor::get_animation()->selection_change(1, 0);
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

        if (PRESSED(KEY_ENTER)) {
            editor::get_animation()->frame_push_back();
        }

        if (PRESSED(KEY_Q)) {
            editor::get_animation()->frame_prev();
        }

        if (PRESSED(KEY_E)) {
            editor::get_animation()->frame_next();
        }

        if (PRESSED(KEY_A)) {
            editor::get_animation()->selection_all();
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
            } else {
                editor::export_file(editor::get_file_open());
            }
        }

        if (PRESSED(KEY_R)) {
            ui::position_windows = true;
        }
    }

    void imgui() {
        ImGui::Text("Shortcuts: ");

        ImGui::Text("====================================");
        ImGui::Text("NUM 1-9      Change view id");
        ImGui::Text("~            Hide imgui rendering");
        ImGui::Text("Q            Previous background");
        ImGui::Text("E            Next background");
        ImGui::Text("CTRL+Q       Previous frame");
        ImGui::Text("CTRL+E       Next frame");
        ImGui::Text("ARROWS       Move for 1 pixel");
        ImGui::Text("CTRL+SPACE   New point");
        ImGui::Text("CTRL+ENTER   New frame");
        ImGui::Text("CTRL+DELETE  Delete selected points");
        ImGui::Text("CTRL+A       Select all points");
        ImGui::Text("CTRL+C       Copy points");
        ImGui::Text("CTRL+V       Paste points");
        ImGui::Text("CTRL+S       Export to file");
        ImGui::Text("CTRL+O       Import from file");
        ImGui::Text("CTRL+R       Reset workplace");
        ImGui::Text("====================================");
    }

}

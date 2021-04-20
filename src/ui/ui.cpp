#include "imgui.h"

#include "editor/editor.h"
#include "imgui/modal.h"

using namespace ImGui;

namespace ui {

    void update() {
        if (BeginMainMenuBar()) {
            if (BeginMenu("File")) {
                if (MenuItem("New")) { editor::create_new(); }
                Separator();
                if (MenuItem("Import", "CTRL+I")) { modal::open(); }
                if (MenuItem("Export", "CTRL+E")) { modal::open(); }

                EndMenu();
            }

            EndMainMenuBar();
        }
    }

}

#include "imgui.h"

#include "editor/editor.h"
#include "imgui/modal.h"
#include "views/views.h"

using namespace ImGui;

namespace ui {

    void update() {
        static bool window_master = true;
        static bool window_points = true;

        if (BeginMainMenuBar()) {
            if (BeginMenu("File")) {
                if (MenuItem("New")) { editor::create_new(); }
                Separator();
                if (MenuItem("Import", "CTRL+I")) { modal::open(); }
                if (MenuItem("Save", "CTRL+S")) { modal::open(); }

                EndMenu();
            }

            if (BeginMenu("View")) {
                RadioButton(MASTER_NAME, editor::get_view(), MASTER_ID);
                RadioButton(POINTS_NAME, editor::get_view(), POINTS_ID);
                RadioButton("Z oreder view", editor::get_view(), 2);
                RadioButton("Foreground view", editor::get_view(), 3);
                RadioButton("Ground view", editor::get_view(), 4);
                RadioButton("Background view", editor::get_view(), 5);

                EndMenu();
            }

            if (BeginMenu("Window")) {
                if (MenuItem(MASTER_NAME, "", window_master)) { window_master = !window_master; }
                if (MenuItem(POINTS_NAME, "", window_points)) { window_points = !window_points; }

                EndMenu();
            }

            if (BeginMenu("Animation")) {
                if (MenuItem("New Point")) { editor::new_point(); }
                if (MenuItem("New Frame")) { editor::new_frame(); }

                Separator();

                if (MenuItem("New Animation")) { editor::new_animation(); }

                EndMenu();
            }

            EndMainMenuBar();
        }

        if (window_master) {
            Begin(MASTER_NAME, &window_master);
            master::imgui();
            End();
        }

        if (window_points) {
            Begin(POINTS_NAME, &window_points);
            points::imgui();
            End();
        }
    }

}

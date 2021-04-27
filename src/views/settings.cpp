#include <imgui.h>

#include "editor/editor.h"
#include "util/ini.h"

#define INI_FILE_NAME "sk.ini"

struct property_t {
    char* name;
    void* val;
    int type;
};

static property_t properties[] {
    { "precise_select", &editor::precise_select }
};

namespace settings {

    void save();

    void imgui() {
        if (ImGui::Button("Save settings")) {
            save();
        }

        ImGui::SameLine();
        ImGui::Text("Settings: ");
        ImGui::Checkbox("Precise select", &editor::precise_select);
    }

    void read() {
        INIReader reader(INI_FILE_NAME);

        if (reader.ParseError() != 0) {
            return;
        }

        // TODO:

        // std::cout << "Config loaded from 'test.ini': version="
        //         << reader.GetInteger("protocol", "version", -1) << ", name="
        //         << reader.Get("user", "name", "UNKNOWN") << ", email="
        //         << reader.Get("user", "email", "UNKNOWN") << ", pi="
        //         << reader.GetReal("user", "pi", -1) << ", active="
        //         << reader.GetBoolean("user", "active", true) << "\n";
    }

    void save() {
        for (int i = 0; i < IM_ARRAYSIZE(properties); i++) {
            // properties[i].
        }
    }

}

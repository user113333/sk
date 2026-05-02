#include "editor.hpp"

#include "core.hpp"

using namespace Sk;

void Editor::Update(Pack &pack)
{
    modes.Update();
}

void Editor::Render(Pack &pack)
{
    // Render center
    DrawRectangle(-2, -8, 4, 16, COLOR_WHITE50);
    DrawRectangle(-8, -2, 16, 4, COLOR_WHITE50);

    pack.Background.Render();

    modes.Render();
}

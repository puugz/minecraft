#include <stb_image.h>

#include "app.h"
#include "window.h"

using namespace minecraft;

int main()
{
#ifdef MINECRAFT_DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    Window window("minecraft++", 1280, 720);

    stbi_set_flip_vertically_on_load(true);

    App app(window);

    app.init_imgui();
    app.run();

    return 0;
}

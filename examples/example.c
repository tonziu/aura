// First example:
// - 1. Open a window
#include "aura.h"

int main(void)
{
    aura_Window_t window;
    aura_InitWindow(600, 400, "My first Window", &window);

    while (!aura_WindowShouldClose(&window))
    {
        aura_BeginFrame(&window);
        aura_EndFrame(&window);
    }

    aura_CloseWindow(&window);

    return 0;
}

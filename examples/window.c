// First example:
// - 1. Open a window
#include "aura.h"
#include <stdio.h>

int main(void)
{
    aura_Window_t window;
    if (aura_InitWindow(600, 400, "My first Window", &window) == AURA_FAILURE)
    {
        printf("Error: could not initialize window.\n");
        return 1;
    }

    while (!aura_WindowShouldClose(&window))
    {
        aura_BeginFrame(&window);
        aura_EndFrame(&window);
    }

    aura_CloseWindow(&window);

    return 0;
}

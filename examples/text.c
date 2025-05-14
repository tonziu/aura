#include "aura.h"
#include <stdio.h>

int main(void)
{
    int screen_width = 800;
    int screen_height = 600;

    aura_Window_t window;
    if (aura_InitWindow(screen_width, screen_height, "Text", &window) == AURA_FAILURE)
    {
        printf("Error: could not initialize window.\n");
        return 1;
    }
    
    aura_Font_t font;
    if (aura_InitFont("../assets/fonts/typewriter/TYPEWR__.TTF", 96, &font) == AURA_FAILURE)
    {
        printf("Error: could not initialize font.\n");
        return 1;
    }

    aura_SetFontProjection(0, screen_width, screen_height, 0, -1, 1, &font);

    vec3 textcolor = {0.88, 0.88, 0.88};
    aura_SetFontColor(textcolor, &font);
    
    aura_SetBackgroundColorF(0.1f, 0.12f, 0.15f, 1.0f);

    while (!aura_WindowShouldClose(&window))
    {
        aura_BeginFrame(&window);
        aura_DrawText("Hello from Aura!", 200, 250, 0.5f, textcolor, &font);
        aura_EndFrame(&window);
    }
    
    aura_CloseFont(&font);
    aura_CloseWindow(&window);

    return 0;
}

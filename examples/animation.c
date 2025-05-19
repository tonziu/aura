#include "aura.h"

int main(void)
{
    aura_Context ctx;
    aura_Renderer renderer;

    context_Init(800, 600, "Animation", &ctx);
    renderer_Init(800, 600, &renderer);

    context_ClearColor(AURA_RETRO_GREEN, &ctx);

    aura_Spritesheet spritesheet = {0};
    spritesheet_Init("../resources/images/man-idle.png", &spritesheet);

    spritesheet.sprite.x = 150;
    spritesheet.sprite.y = 100;
    spritesheet.sprite.w = 450;
    spritesheet.sprite.h = 450;
    spritesheet.rows = 1;
    spritesheet.cols = 10;
    spritesheet.timer.rate = 0.08;
    spritesheet.timer.start = glfwGetTime();

    int row = 0;

    while (!context_WindowShouldClose(&ctx))
    {
        context_BeginFrame(&ctx);
        double now = glfwGetTime();
        spritesheet_Tick(now, &spritesheet);

        renderer_DrawSpritesheet(spritesheet, row, &renderer);

        context_EndFrame(&ctx);
    }

    context_Close(&ctx);
    return 0;
}

#include "aura.h"

#define SCREEN_W 800
#define SCREEN_H 600

int main(void)
{
    aura_Context ctx;
    aura_Renderer renderer;

    context_Init(SCREEN_W, SCREEN_H, "Sprite", &ctx);
    renderer_Init(SCREEN_W, SCREEN_H, &renderer);

    context_ClearColor(AURA_RETRO_GREEN, &ctx);

    aura_Sprite sprite = {0};
    sprite_Init("../resources/images/aura_logo_medium.png", &sprite);

    sprite.x = 250;
    sprite.y = 0;
    sprite.w = 300;
    sprite.h = 300;

    float vy = 0;
    float acc = 2500.0;

    double last = glfwGetTime();
    double dt = 0;
    double now = last;

    aura_Rectangle rect = {0, SCREEN_H - 100, SCREEN_W, 100};

    while (!context_WindowShouldClose(&ctx))
    {
        context_BeginFrame(&ctx);

        now = glfwGetTime();
        dt = now - last; 
        last = now;
        vy += acc * dt;
        sprite.y += vy * dt;

        if (sprite.y + sprite.h >= rect.y)
        {
            vy *= -0.8;
            sprite.y = rect.y - sprite.h;
        }

        renderer_DrawSprite(sprite, &renderer);
        renderer_DrawRectangle(rect, AURA_RETRO_BROWN, &renderer);

        context_EndFrame(&ctx);
    }

    context_Close(&ctx);

    return 0;
}

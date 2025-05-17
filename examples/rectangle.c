#include "aura.h"

#define SCREEN_W 800
#define SCREEN_H 600

int main(void)
{
    int ret;
    aura_Context ctx;
    aura_Renderer renderer;

    ret = context_Init(SCREEN_W, SCREEN_H, "Rectangle", &ctx);
    if (ret == AURA_ERROR) return AURA_ERROR;

    ret = renderer_Init(SCREEN_W, SCREEN_H, &renderer);
    if (ret == AURA_ERROR) return AURA_ERROR;

    aura_Color bgcolor = {22 / 255.0f, 22 / 255.0f, 22 / 255.0f, 1.0f};
    context_ClearColor(bgcolor, &ctx);

    aura_Rectangle rect = {200, 200, 400, 200};
    aura_Color rectcolor = {20 / 255.0f, 250 / 255.0f, 80 / 255.0f, 1.0f};
    vec3 axis = {0, 0, -1};
    float angle = glm_rad(45);

    while (!context_WindowShouldClose(&ctx))
    {
        context_BeginFrame(&ctx);
        // renderer_DrawRectangle(rect, rectcolor, &renderer);
        renderer_DrawRectangleEx(rect, rectcolor, angle, axis, &renderer);
        angle += 0.01f;
        context_EndFrame(&ctx);
    }

    context_Close(&ctx);

    return AURA_OK;
}

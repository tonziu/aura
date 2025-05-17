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

    ret = renderer_Init(&renderer, SCREEN_W, SCREEN_H);
    if (ret == AURA_ERROR) return AURA_ERROR;

    aura_Color bgcolor = {22, 22, 22, 255};
    context_SetBgColor(bgcolor, &ctx);

    aura_Rectangle rect = {200, 200, 400, 200};

    while (!context_WindowShouldClose(&ctx))
    {
        context_BeginFrame(&ctx);
        renderer_DrawRectangle(rect, &renderer);
        context_EndFrame(&ctx);
    }

    context_Close(&ctx);

    return AURA_OK;
}

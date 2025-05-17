#include "aura.h"

#define SCREEN_W 600
#define SCREEN_H 400

int main(void)
{
    aura_Context ctx;

    if (context_Init(600, 400, "My First Window", &ctx) != AURA_OK)
    {
        return AURA_ERROR;
    }

    aura_Color bgcolor = {22, 22, 22, 255};
    context_SetBgColor(bgcolor, &ctx);

    while (!context_WindowShouldClose(&ctx))
    {
        context_BeginFrame(&ctx);
        context_EndFrame(&ctx);
    }

    context_Close(&ctx);

    return AURA_OK;
}

#include "aura.h"

#define SCREEN_W 800
#define SCREEN_H 600

int main(void)
{
    int ret;
    aura_Context ctx;
    aura_Renderer renderer;
    aura_TextRenderer textrenderer;

    ret = context_Init(SCREEN_W, SCREEN_H, "Text", &ctx);
    if (ret == AURA_ERROR) return AURA_ERROR;

    ret = renderer_Init(SCREEN_W, SCREEN_H, &renderer);
    if (ret == AURA_ERROR) return AURA_ERROR;

    ret = textrenderer_Init(SCREEN_W, SCREEN_H, &textrenderer);
    if (ret == AURA_ERROR) return AURA_ERROR;

    aura_Color bgcolor = {22 / 255.0f, 22 / 255.0f, 22 / 255.0f, 1.0f};
    context_ClearColor(bgcolor, &ctx);

    aura_Color textcolor = {0.1, 0.8, 0.8, 1.0};

    const char* text = "Hello From Aura!";
    float textscale = 1.0f;
    float textwidth = textrenderer_MeasureText(text, textscale, &textrenderer);

    while (!context_WindowShouldClose(&ctx))
    {
        context_BeginFrame(&ctx);

        textrenderer_DrawText(text, 
                               SCREEN_W / 2.0f - textwidth / 2, 250, 
                               textscale, 
                               textcolor, 
                               &textrenderer);

        context_EndFrame(&ctx);
    }

    context_Close(&ctx);

    return AURA_OK;
}

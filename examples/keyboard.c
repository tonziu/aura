#include "aura.h"

#define SCREEN_W 800
#define SCREEN_H 600

typedef enum
{
    INTRO,
    QUIT,
} Scene;

int main(void)
{
    aura_Context ctx;
    aura_Renderer renderer;
    aura_TextRenderer textRenderer;

    context_Init(SCREEN_W, SCREEN_H, "Keyboard", &ctx);
    renderer_Init(SCREEN_W, SCREEN_H, &renderer);
    textrenderer_Init(SCREEN_W, SCREEN_H, &textRenderer);

    context_ClearColor(AURA_RETRO_GREEN, &ctx);

    Scene curr_scene = INTRO;

    const char* textA = "Press SPACE to change scene";
    const char* textB = "Press ESC to quit.";

    float textA_width = textrenderer_MeasureText(textA, 1, &textRenderer);
    float textB_width = textrenderer_MeasureText(textB, 1, &textRenderer);

    while (!context_WindowShouldClose(&ctx))
    {
        context_BeginFrame(&ctx);

        if (curr_scene == INTRO && context_KeyIsPressed(GLFW_KEY_SPACE, &ctx))
        {
            curr_scene = QUIT;
        }
        else if (curr_scene == QUIT && context_KeyIsPressed(GLFW_KEY_ESCAPE, &ctx))
        {
            context_CloseWindow(&ctx);
        }

        switch (curr_scene)
        {
        case INTRO:
            textrenderer_DrawText(textA, SCREEN_W / 2.0f - textA_width / 2.0f,
                                         SCREEN_H / 2.0f - 50,
                                         1.0, AURA_RETRO_YELLOW,
                                         &textRenderer);
            break;
        case QUIT:
            textrenderer_DrawText(textB, SCREEN_W / 2.0f - textB_width / 2.0f,
                                         SCREEN_H / 2.0f - 50,
                                         1.0, AURA_RETRO_YELLOW,
                                         &textRenderer);
            break;
        default:
            break;
        }
        context_EndFrame(&ctx);
    }

    context_Close(&ctx);

    return 0;
}

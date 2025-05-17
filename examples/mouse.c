#include "aura.h"

#define SCREEN_W 800
#define SCREEN_H 600

typedef enum
{
    LOGO,
    PLAY,
    END
} Scene;

typedef enum
{
    OFF,
    ON,
} Toggle;

bool click_inside(aura_Rectangle r, double posx, double posy)
{
    bool ret = posx > r.x && posx < r.x + r.w && 
               posy > r.y && posy < r.y + r.h;
    return ret;
}

int main(void)
{
    aura_Context ctx;
    aura_Renderer renderer;
    aura_TextRenderer textRenderer;

    context_Init(SCREEN_W, SCREEN_H, "Mouse", &ctx);
    renderer_Init(SCREEN_W, SCREEN_H, &renderer);
    textrenderer_Init(SCREEN_W, SCREEN_H, &textRenderer);

    context_ClearColor(AURA_RETRO_GREEN, &ctx);

    Scene scene = LOGO;

    aura_Sprite logo = {0};
    sprite_Init("../resources/images/aura_logo_medium.png", &logo);
    logo.w = 200;
    logo.h = 200;
    logo.x = SCREEN_W / 2.0f - logo.w / 2.0f;
    logo.y = SCREEN_H / 2.0f - logo.h / 2.0f;

    aura_Rectangle r1 = {200, 100, 50, 50};
    aura_Rectangle r2 = {550, 100, 50, 50};
    aura_Rectangle r3 = {200, 450, 50, 50};
    aura_Rectangle r4 = {550, 450, 50, 50};

    aura_Color cr1 = AURA_RETRO_WHITE;
    aura_Color cr2 = AURA_RETRO_WHITE;
    aura_Color cr3 = AURA_RETRO_WHITE;
    aura_Color cr4 = AURA_RETRO_WHITE;

    Toggle tr1 = OFF;
    Toggle tr2 = OFF;
    Toggle tr3 = OFF;
    Toggle tr4 = OFF;

    const char* text = "Try and click the squares!";
    float tw = textrenderer_MeasureText(text, 1, &textRenderer);

    const char* endtext = "Well done! Press ESC to exit.";
    float etw = textrenderer_MeasureText(endtext, 0.8, &textRenderer);

    double elapsed = 0;
    double mousex = 0;
    double mousey = 0;

    while (!context_WindowShouldClose(&ctx))
    {
        context_BeginFrame(&ctx);

        elapsed = glfwGetTime();
        if (scene == LOGO && elapsed > 1)
        {
            scene = PLAY;
        }

        context_GetMousePos(&mousex, &mousey, &ctx);
        if (scene == PLAY && context_MouseIsPressed(GLFW_MOUSE_BUTTON_LEFT, &ctx))
        {
            if (click_inside(r1, mousex, mousey) && tr1 == OFF)
            {
                tr1 = ON;
            }
            else if (click_inside(r2, mousex, mousey) && tr2 == OFF)
            {
                tr2 = ON;
            }
            else if (click_inside(r3, mousex, mousey) && tr3 == OFF)
            {
                tr3 = ON;
            }
            else if (click_inside(r4, mousex, mousey) && tr4 == OFF)
            {
                tr4 = ON;
            }
        }

        if (tr1 == ON && tr2 == ON && tr3 == ON && tr4 == ON)
        {
            scene = END;
        }

        if (scene == END && context_KeyIsPressed(GLFW_KEY_ESCAPE, &ctx))
        {
            context_CloseWindow(&ctx);
        }

        switch (scene)
        {
        case LOGO:
        {
            renderer_DrawSprite(logo, &renderer);
            break;
        }
        case PLAY:
        {
            if (tr1 == ON) cr1 = AURA_RETRO_RED;
            if (tr2 == ON) cr2 = AURA_RETRO_RED;
            if (tr3 == ON) cr3 = AURA_RETRO_RED;
            if (tr4 == ON) cr4 = AURA_RETRO_RED;

            renderer_DrawRectangle(r1, cr1, &renderer);
            renderer_DrawRectangle(r2, cr2, &renderer);
            renderer_DrawRectangle(r3, cr3, &renderer);
            renderer_DrawRectangle(r4, cr4, &renderer);

            textrenderer_DrawText(text, SCREEN_W/2.0f - tw/2.0f, 280, 1.0f, 
                    AURA_RETRO_YELLOW, &textRenderer);
            break;
        }
        case END:
        {
            textrenderer_DrawText(endtext, SCREEN_W/2.0f - etw/2.0f, 280, 0.8f,
                    AURA_RETRO_YELLOW, &textRenderer);
        }
        default:
            break;
        }

        context_EndFrame(&ctx);
    }

    context_Close(&ctx);

    return 0;
}

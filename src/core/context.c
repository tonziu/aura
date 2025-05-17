#include "aura.h"

int context_Init(int w, int h, const char* title, aura_Context* ctx)
{
    if (!glfwInit()) return AURA_ERROR;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    ctx->window = glfwCreateWindow(w, h, title, NULL, NULL);

    if (!ctx->window) return AURA_ERROR;

    glfwMakeContextCurrent(ctx->window);
    glfwSwapInterval(1);
    
    if (!gladLoadGL()) return AURA_ERROR;

    glViewport(0, 0, w, h);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    GLFWimage icon_image_xs;
    GLFWimage icon_image_s;
    GLFWimage icon_image_m;
    GLFWimage icon_image_l;

    GLFWimage icons[4];
    utils_LoadImage("../resources/images/aura_logo_extrasmall.png", &icons[0]);
    utils_LoadImage("../resources/images/aura_logo_small.png", &icons[1]);
    utils_LoadImage("../resources/images/aura_logo_medium.png", &icons[2]);
    utils_LoadImage("../resources/images/aura_logo_large.png", &icons[3]);
    glfwSetWindowIcon(ctx->window, 4, icons);

    for (int i = 0; i < 4; ++i)
    {
        utils_FreeImage(&icons[i]);
    }

    return AURA_OK;
}

bool context_WindowShouldClose(aura_Context* ctx)
{
    return glfwWindowShouldClose(ctx->window);
}

void context_BeginFrame(aura_Context* ctx)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void context_EndFrame(aura_Context* ctx)
{
    glfwPollEvents();
    glfwSwapBuffers(ctx->window);
    glFinish();
}

void context_ClearColor(aura_Color color, aura_Context* ctx)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void context_Close(aura_Context* ctx)
{
    glfwDestroyWindow(ctx->window);
    glfwTerminate();
}

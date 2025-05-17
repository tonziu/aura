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

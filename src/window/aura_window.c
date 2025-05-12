#include "aura.h"

int aura_InitWindow(int width, int height, const char* title, aura_Window_t* window)
{
    if (!glfwInit()) return AURA_FAILURE;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window->win_ptr = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window->win_ptr) return AURA_FAILURE;

    glfwMakeContextCurrent(window->win_ptr);
    glfwSwapInterval(1);

    if (!gladLoadGL()) return AURA_FAILURE;

    glViewport(0, 0, width, height);

    return AURA_SUCCESS;
}

bool aura_WindowShouldClose(aura_Window_t* window)
{
    return glfwWindowShouldClose(window->win_ptr);
}

void aura_BeginFrame(aura_Window_t* window)
{
    glfwPollEvents();
}

void aura_EndFrame(aura_Window_t* window)
{
    glfwSwapBuffers(window->win_ptr);
    glFinish();
}

void aura_CloseWindow(aura_Window_t* window)
{
    if (window->win_ptr) glfwDestroyWindow(window->win_ptr);
    glfwTerminate();
}

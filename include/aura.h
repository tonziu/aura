#ifndef H_AURA_H
#define H_AURA_H

#include <stdbool.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define AURA_SUCCESS 1
#define AURA_FAILURE 0

typedef struct
{
    GLFWwindow* win_ptr;
} aura_Window_t;

int aura_InitWindow(int width, int height, const char* title, aura_Window_t* window);

bool aura_WindowShouldClose(aura_Window_t* window);

void aura_BeginFrame(aura_Window_t* window);

void aura_EndFrame(aura_Window_t* window);

void aura_CloseWindow(aura_Window_t* window);

#endif // H_AURA_H

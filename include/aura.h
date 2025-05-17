#ifndef H_AURA_H
#define H_AURA_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdbool.h>

#define AURA_OK    0
#define AURA_ERROR 1

typedef struct
{
    int r;
    int g;
    int b;
    int a;
} aura_Color;

typedef struct
{
    GLFWwindow* window;
    float bgcolor[4];
} aura_Context;

// Context Functions

int context_Init(int w, int h, const char* title, aura_Context* ctx);
bool context_WindowShouldClose(aura_Context* ctx);
void context_BeginFrame(aura_Context* ctx);
void context_EndFrame(aura_Context* ctx);
void context_SetBgColor(aura_Color color, aura_Context* ctx);
void context_Close(aura_Context* ctx);

#endif // H_AURA_H

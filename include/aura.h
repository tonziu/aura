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

typedef struct
{
    float x;
    float y;
    float w;
    float h;
} aura_Rectangle;

typedef struct
{
    GLuint vao;
    GLuint vbo;
} aura_Mesh;

typedef struct
{
    int index;
    int size;
    int stride;
    int offset;
} aura_VertexAttributeF;

typedef struct
{
    GLuint program;
} aura_Material; 

typedef struct
{
    aura_Material material;
    aura_Mesh mesh;
} aura_Renderable;

typedef struct
{
    aura_Renderable rectangle;
} aura_Renderer;

// -------------------------------------------------------------------------------
// Context Functions
// -------------------------------------------------------------------------------

int  context_Init(int w, int h, const char* title, aura_Context* ctx);
bool context_WindowShouldClose(aura_Context* ctx);
void context_BeginFrame(aura_Context* ctx);
void context_EndFrame(aura_Context* ctx);
void context_SetBgColor(aura_Color color, aura_Context* ctx);
void context_Close(aura_Context* ctx);

// -------------------------------------------------------------------------------



// -------------------------------------------------------------------------------
// Mesh functions
// -------------------------------------------------------------------------------

void mesh_InitBuffers(float* vertices, int num_vertices,
                      GLenum usage, aura_Mesh* mesh);

void mesh_AddAttributeF(aura_VertexAttributeF attr, aura_Mesh* mesh);

// -------------------------------------------------------------------------------



// -------------------------------------------------------------------------------
// Utilities functions
// -------------------------------------------------------------------------------

int utils_ReadTextFile(const char* filename, char* buffer, int len);

// -------------------------------------------------------------------------------


// -------------------------------------------------------------------------------
// Material functions
// -------------------------------------------------------------------------------

int material_CompileShader(const char* src, GLenum type, GLuint* shader);
int material_LinkProgram(const char* vsrc, const char* fsrc,
                                               aura_Material* material);
int material_InitProgram(const char* vs_path, const char* fs_path, 
                                               aura_Material* material);

// -------------------------------------------------------------------------------



// -------------------------------------------------------------------------------
// Renderable functions
// -------------------------------------------------------------------------------

int renderable_Rectangle(aura_Renderable* renderable);

// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// Renderer functions
// -------------------------------------------------------------------------------

int renderer_Init(aura_Renderer* renderer);
void renderer_DrawRectangle(aura_Renderer* renderer);

// -------------------------------------------------------------------------------

#endif // H_AURA_H

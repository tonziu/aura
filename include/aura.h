#ifndef H_AURA_H
#define H_AURA_H

#include <stdbool.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"

#define AURA_SUCCESS 1
#define AURA_FAILURE 0

#define AURA_MAX_CHARS 128

typedef struct
{
    GLFWwindow* win_ptr;
} aura_Window_t;

typedef struct
{
    GLuint VAO;
    GLuint VBO;
} aura_Mesh_t;

typedef struct
{
    GLuint program;
} aura_Material_t;

typedef struct
{
    GLuint texture;
    float width;
    float height;
    float bearingx;
    float bearingy;
    GLuint advance;
} aura_Glyph_t;

typedef struct
{
    aura_Glyph_t glyphs[AURA_MAX_CHARS]; 
    aura_Mesh_t mesh; 
    aura_Material_t material;
} aura_Font_t;

int aura_InitWindow(int width, int height, const char* title, aura_Window_t* window);
void aura_SetBackgroundColorF(float r, float g, float b, float a);

int aura_InitFont(const char* filename, int pixel_height, aura_Font_t* font);
void aura_CloseFont(aura_Font_t* font);
void aura_SetFontProjection(float left, float right,
                           float bottom, float top,
                           float near, float far, aura_Font_t* font);
void aura_SetFontColor(vec3 color, aura_Font_t* font);

void aura_DrawText(const char* text, float x, float y, float scale, vec3 color,
                   aura_Font_t* font);

bool aura_WindowShouldClose(aura_Window_t* window);

void aura_BeginFrame(aura_Window_t* window);

void aura_EndFrame(aura_Window_t* window);

void aura_CloseWindow(aura_Window_t* window);

int aura_CompileShader(const char* src, GLenum type, GLuint* shader);
int aura_LinkProgram(GLuint vshader, GLuint fshader, GLuint* program);
int aura_SetProgramUniform_3f(GLuint program, const char* name, float x, 
                                                                float y, 
                                                                float z);
int aura_SetProgramUniform_Mat4(GLuint program, const char* name, mat4 m);

#endif // H_AURA_H

#ifndef H_AURA_H
#define H_AURA_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include <stdbool.h>

#define AURA_OK    0
#define AURA_ERROR 1
#define AURA_MAX_GLYPHS 128
#define AURA_RETRO_GREEN (aura_Color){75 / 255.0f, 105 / 255.0f, 47 / 255.0f, 1.0f}
#define AURA_RETRO_YELLOW (aura_Color){228 / 255.0f, 216 / 255.0f, 172 / 255.0f, 1.0}
#define AURA_RETRO_BROWN (aura_Color){102 / 255.0f, 57 / 255.0f, 49 / 255.0f, 1.0}

typedef struct
{
    float r;
    float g;
    float b;
    float a;
} aura_Color;

typedef struct
{
    int prev_state[GLFW_KEY_LAST + 1];
    int curr_state[GLFW_KEY_LAST + 1];
    bool consumed[GLFW_KEY_LAST + 1];
} aura_Keyboard;

typedef struct
{
    int prev_state[GLFW_MOUSE_BUTTON_LAST + 1];
    int curr_state[GLFW_MOUSE_BUTTON_LAST + 1];
    bool consumed[GLFW_MOUSE_BUTTON_LAST + 1];
} aura_Mouse;

typedef struct
{
    GLFWwindow* window;
    aura_Keyboard keyboard;
    aura_Mouse mouse;
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
    aura_Renderable sprite;
} aura_Renderer;

typedef struct
{
    GLuint texture;
    float w;
    float h;
    float bearingx;
    float bearingy;
    GLuint advance;
} aura_Glyph;

typedef struct
{
    FT_Face face;
    aura_Glyph glyphs[AURA_MAX_GLYPHS];
} aura_Font;

typedef struct
{
    FT_Library ft;
    aura_Font font;
    aura_Renderable text;
} aura_TextRenderer;

typedef struct
{
    GLuint texture;
    float x;
    float y;
    float w;
    float h;
    vec3 axis;
    float angle;
} aura_Sprite;

// -------------------------------------------------------------------------------
// Context Functions
// -------------------------------------------------------------------------------

int  context_Init(int w, int h, const char* title, aura_Context* ctx);
bool context_WindowShouldClose(aura_Context* ctx);
void context_BeginFrame(aura_Context* ctx);
void context_EndFrame(aura_Context* ctx);
void context_ClearColor(aura_Color color, aura_Context* ctx);
void context_Close(aura_Context* ctx);
bool context_KeyIsPressed(int key, aura_Context* ctx);
void context_CloseWindow(aura_Context* ctx);

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
int utils_LoadImage(const char* filename, GLFWimage* image);
void utils_FreeImage(GLFWimage* image);
// -------------------------------------------------------------------------------


// -------------------------------------------------------------------------------
// Material functions
// -------------------------------------------------------------------------------

int material_CompileShader(const char* src, GLenum type, GLuint* shader);
int material_LinkProgram(const char* vsrc, const char* fsrc,
                                               aura_Material* material);
int material_InitProgram(const char* vs_path, const char* fs_path, 
                                               aura_Material* material);
int material_GetUniformLocation(const char* name, int* loc, aura_Material* material);
int material_SetUniformMat4(mat4 data, const char* name, aura_Material* material);
int material_SetUniformVec4(vec4 data, const char* name, aura_Material* material);

// -------------------------------------------------------------------------------



// -------------------------------------------------------------------------------
// Renderable functions
// -------------------------------------------------------------------------------

int renderable_Rectangle(int screen_w, int screen_h, aura_Renderable* renderable);
int renderable_Text(int screen_w, int screen_h, aura_Renderable* renderable);
int renderable_Sprite(int screen_w, int screen_h, aura_Renderable* renderable);

// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// Renderer functions
// -------------------------------------------------------------------------------

int renderer_Init(int screen_w, int screen_h, aura_Renderer* renderer);
void renderer_DrawRectangle(aura_Rectangle rect, aura_Color color,
                            aura_Renderer* renderer);
void renderer_DrawRectangleEx(aura_Rectangle rect, aura_Color color,
                            float angle, vec3 axis, aura_Renderer* renderer);
void renderer_DrawSprite(aura_Sprite sprite, aura_Renderer* renderer);

// -------------------------------------------------------------------------------



// -------------------------------------------------------------------------------
// Glyph functions
// -------------------------------------------------------------------------------

void glyph_Init(FT_Face face, unsigned char c, aura_Glyph* glyph);

// -------------------------------------------------------------------------------



// -------------------------------------------------------------------------------
// Font functions
// -------------------------------------------------------------------------------

void font_InitGlyphs(aura_Font* font);
int font_Init(const char* filename, FT_Library ft, aura_Font* font);
// -------------------------------------------------------------------------------



// -------------------------------------------------------------------------------
// Text Renderer functions
// -------------------------------------------------------------------------------

int textrenderer_Init(int screen_w, int screen_h, aura_TextRenderer* renderer);
void textrenderer_DrawText(const char* text, 
                           float x, float y, float scale, aura_Color color,
                           aura_TextRenderer* renderer);
float textrenderer_MeasureText(const char* text, float scale, 
                                aura_TextRenderer* renderer);
// -------------------------------------------------------------------------------/

// -------------------------------------------------------------------------------
// Sprite functions
// -------------------------------------------------------------------------------

int sprite_Init(const char* image, aura_Sprite* sprite);

// -------------------------------------------------------------------------------

#endif // H_AURA_H

#include "aura.h"

int renderable_Rectangle(int screen_w, int screen_h, aura_Renderable* renderable)
{
    int ret = material_InitProgram("../resources/shaders/rect.vs", 
                                   "../resources/shaders/rect.fs",
                                   &renderable->material);

    if (ret == AURA_ERROR) return AURA_ERROR;

    glUseProgram(renderable->material.program);
    mat4 proj;
    glm_ortho(0, screen_w, screen_h, 0, -1, 1, proj);
    ret = material_SetUniformMat4(proj, "projection", &renderable->material);
    glUseProgram(0);

    if (ret == AURA_ERROR) return AURA_ERROR;
    
    float vertices[12] =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,

         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,
    };

    aura_VertexAttributeF pos_attr = {0, 2, 2, 0};
    mesh_InitBuffers(vertices, 12, GL_STATIC_DRAW, &renderable->mesh);
    mesh_AddAttributeF(pos_attr, &renderable->mesh);

    return AURA_OK;
}

int renderable_Text(int screen_w, int screen_h, aura_Renderable* renderable)
{
    int ret = material_InitProgram("../resources/shaders/text.vs", 
                                   "../resources/shaders/text.fs",
                                   &renderable->material);

    if (ret == AURA_ERROR) return AURA_ERROR;

    glUseProgram(renderable->material.program);
    mat4 proj;
    glm_ortho(0, screen_w, screen_h, 0, -1, 1, proj);
    ret = material_SetUniformMat4(proj, "projection", &renderable->material);
    glUseProgram(0);

    if (ret == AURA_ERROR) return AURA_ERROR;
    
    float vertices[24] = {0};

    aura_VertexAttributeF pos_attr = {0, 4, 4, 0};
    mesh_InitBuffers(vertices, 24, GL_DYNAMIC_DRAW, &renderable->mesh);
    mesh_AddAttributeF(pos_attr, &renderable->mesh);

    return AURA_OK;
}

int renderable_Sprite(int screen_w, int screen_h, aura_Renderable* renderable)
{
    int ret = material_InitProgram("../resources/shaders/sprite.vs", 
                                   "../resources/shaders/sprite.fs",
                                   &renderable->material);

    if (ret == AURA_ERROR) return AURA_ERROR;

    glUseProgram(renderable->material.program);
    mat4 proj;
    glm_ortho(0, screen_w, screen_h, 0, -1, 1, proj);
    ret = material_SetUniformMat4(proj, "projection", &renderable->material);
    glUseProgram(0);

    if (ret == AURA_ERROR) return AURA_ERROR;
    
    float vertices[24] =
    {
        -0.5f, -0.5f, 0, 0,
         0.5f, -0.5f, 1, 0,
         0.5f,  0.5f, 1, 1,

         0.5f,  0.5f, 1, 1,
        -0.5f,  0.5f, 0, 1,
        -0.5f, -0.5f, 0, 0
    };

    aura_VertexAttributeF pos_attr = {0, 2, 4, 0};
    aura_VertexAttributeF tex_attr = {1, 2, 4, 2};
    mesh_InitBuffers(vertices, 24, GL_STATIC_DRAW, &renderable->mesh);
    mesh_AddAttributeF(pos_attr, &renderable->mesh);
    mesh_AddAttributeF(tex_attr, &renderable->mesh);

    return AURA_OK;
}

int renderable_Spritesheet(int screen_w, int screen_h, aura_Renderable* renderable)
{
    int ret = material_InitProgram("../resources/shaders/spritesheet.vs", 
                                   "../resources/shaders/spritesheet.fs",
                                   &renderable->material);

    if (ret == AURA_ERROR) return AURA_ERROR;

    glUseProgram(renderable->material.program);
    mat4 proj;
    glm_ortho(0, screen_w, screen_h, 0, -1, 1, proj);
    ret = material_SetUniformMat4(proj, "projection", &renderable->material);
    glUseProgram(0);

    if (ret == AURA_ERROR) return AURA_ERROR;
    
    float vertices[24] =
    {
        -0.5f, -0.5f, 0, 0,
         0.5f, -0.5f, 1, 0,
         0.5f,  0.5f, 1, 1,

         0.5f,  0.5f, 1, 1,
        -0.5f,  0.5f, 0, 1,
        -0.5f, -0.5f, 0, 0
    };

    aura_VertexAttributeF pos_attr = {0, 2, 4, 0};
    aura_VertexAttributeF tex_attr = {1, 2, 4, 2};
    mesh_InitBuffers(vertices, 24, GL_STATIC_DRAW, &renderable->mesh);
    mesh_AddAttributeF(pos_attr, &renderable->mesh);
    mesh_AddAttributeF(tex_attr, &renderable->mesh);
    return AURA_OK;
}

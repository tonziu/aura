#include "aura.h"

int renderable_Rectangle(aura_Renderable* renderable)
{
    int ret = material_InitProgram("../resources/shaders/rect.vs", 
                                   "../resources/shaders/rect.fs",
                                   &renderable->material);

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

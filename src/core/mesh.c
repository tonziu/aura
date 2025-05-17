#include "aura.h"

void mesh_InitBuffers(float* vertices, int num_vertices,
                      GLenum usage, aura_Mesh* mesh)
{
    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);
    glBindVertexArray(mesh->vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices,
                                  vertices, usage);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void mesh_AddAttributeF(aura_VertexAttributeF attr, aura_Mesh* mesh)
{
    glBindVertexArray(mesh->vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glVertexAttribPointer(attr.index, attr.size, 
                          GL_FLOAT, GL_FALSE, attr.stride * sizeof(float),
                          (void*)(attr.offset*sizeof(float)));
    glEnableVertexAttribArray(attr.index);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

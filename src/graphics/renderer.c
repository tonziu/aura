#include "aura.h"

int renderer_Init(aura_Renderer* renderer)
{
    int ret = renderable_Rectangle(&renderer->rectangle);
    return ret;
}

void renderer_DrawRectangle(aura_Renderer* renderer)
{
    glUseProgram(renderer->rectangle.material.program); 
    glBindVertexArray(renderer->rectangle.mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

#include "aura.h"

int renderer_Init(aura_Renderer* renderer, int screen_w, int screen_h)
{
    int ret = renderable_Rectangle(&renderer->rectangle, screen_w, screen_h);
    return ret;
}

void renderer_DrawRectangle(aura_Rectangle rect, aura_Renderer* renderer)
{
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    vec3 translation = {rect.x, rect.y, 0};
    vec3 scaling = {rect.w, rect.h, 1};
    glm_translate(model, translation);
    glm_scale(model, scaling);

    glUseProgram(renderer->rectangle.material.program); 
    material_SetUniformMat4(model, "model", &renderer->rectangle.material);
    glBindVertexArray(renderer->rectangle.mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

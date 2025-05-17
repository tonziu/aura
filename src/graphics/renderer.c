#include "aura.h"

int renderer_Init(int screen_w, int screen_h, aura_Renderer* renderer)
{
    int ret = renderable_Rectangle(screen_w, screen_h, &renderer->rectangle);
    return ret;
}

void renderer_DrawRectangle(aura_Rectangle rect, aura_Color color,
        aura_Renderer* renderer)
{
    vec3 axis = {0, 0, 0};
    renderer_DrawRectangleEx(rect, color, 0, axis, renderer);
}

void renderer_DrawRectangleEx(aura_Rectangle rect, aura_Color color,
                              float angle, vec3 axis, aura_Renderer* renderer)
{
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    vec3 translation = {rect.x + rect.w/2.0f, rect.y + rect.h/2.0f, 0};
    vec3 scaling = {rect.w, rect.h, 1};
    glm_translate(model, translation);
    glm_rotate(model, angle, axis);
    glm_scale(model, scaling);

    vec4 fillcolor = {color.r, color.g, color.b, color.a};

    glUseProgram(renderer->rectangle.material.program); 
    material_SetUniformMat4(model, "model", &renderer->rectangle.material);
    material_SetUniformVec4(fillcolor, "fillcolor", &renderer->rectangle.material);
    glBindVertexArray(renderer->rectangle.mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

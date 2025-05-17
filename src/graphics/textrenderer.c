#include "aura.h"

int textrenderer_Init(int screen_w, int screen_h, aura_TextRenderer* renderer)
{
    if (FT_Init_FreeType(&renderer->ft))
    {
        return AURA_ERROR;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int ret = font_Init(  
                "../resources/fonts/8-bit-operator/8bitOperatorPlus-Regular.ttf",
                renderer->ft,
                &renderer->font);

    FT_Done_FreeType(renderer->ft);

    renderable_Text(screen_w, screen_h, &renderer->text);

    return ret;
}

void textrenderer_DrawText(const char* text, 
                           float x, float y, float scale, aura_Color color,
                           aura_TextRenderer* renderer)
{
    glUseProgram(renderer->text.material.program);
    vec4 textcolor = {color.r, color.g, color.b, color.a};
    material_SetUniformVec4(textcolor, "textcolor", &renderer->text.material);
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(renderer->text.mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->text.mesh.vbo);

    int len = strlen(text);
    int max_bearingy = 0;
    for (int i = 0; i < len; ++i)
    {
        int by = renderer->font.glyphs[text[i]].bearingy;
        max_bearingy = max_bearingy < by ? by : max_bearingy;
    }

    for (int i = 0; i < len; ++i)
    {
        aura_Glyph g = renderer->font.glyphs[text[i]];
        float w =    g.w * scale;
        float h =    g.h * scale;
        float xpos = x + g.bearingx * scale;
        float ypos = y + (max_bearingy - g.bearingy) * scale;
        
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },  
            { xpos,     ypos,       0.0f, 0.0f },  
            { xpos + w, ypos,       1.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f }
        };

        glBindTexture(GL_TEXTURE_2D, g.texture);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (g.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

float textrenderer_MeasureText(const char* text, float scale, 
                                aura_TextRenderer* renderer)
{
    float w = 0;
    int len = strlen(text);
    for (int i = 0; i < len; ++i)
    {
        w += (renderer->font.glyphs[text[i]].advance >> 6) * scale;
    }
    return w;
}

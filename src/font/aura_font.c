#include "aura.h"

#include "ft2build.h"
#include FT_FREETYPE_H

int font_InitMaterial(aura_Font_t* font)
{
    const char* vsrc =
        "#version 330 core\n"
        "layout(location = 0) in vec4 vertex;\n"
        "out vec2 TexCoords;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "   gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
        "   TexCoords = vertex.zw;\n"
        "}\0";

    const char* fsrc =
        "#version 330 core\n"
        "in vec2 TexCoords;\n"
        "out vec4 color;\n"
        "uniform sampler2D text;\n"
        "uniform vec3 textcolor;\n"
        "void main() {\n"
        "   vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
        "   color = vec4(textcolor, 1.0) * sampled;\n"
        "}\0";

    GLuint vshader, fshader;
    if (aura_CompileShader(vsrc, GL_VERTEX_SHADER, &vshader) == AURA_FAILURE)
    {
        printf("Error: could not compile shader of type %d.\n", GL_VERTEX_SHADER); 
        return AURA_FAILURE;
    }
    
    if (aura_CompileShader(fsrc, GL_FRAGMENT_SHADER, &fshader) == AURA_FAILURE)
    {
        printf("Error: could not compile shader of type %d.\n", GL_FRAGMENT_SHADER); 
        return AURA_FAILURE;
    }

    if (aura_LinkProgram(vshader, fshader, &font->material.program) == AURA_FAILURE)
    {
        printf("Error: could not link program using %d and %d.\n", vshader, fshader);
        return AURA_FAILURE;
    }

    return AURA_SUCCESS;
}

int font_InitGlyph(FT_Face face, unsigned char c, aura_Glyph_t* glyph)
{
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
        printf("Error: could not load %c.\n", c);
        return AURA_FAILURE;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                                        face->glyph->bitmap.width,
                                        face->glyph->bitmap.rows, 
                                        0, GL_RED, GL_UNSIGNED_BYTE,
                                        face->glyph->bitmap.buffer);
    glGenerateMipmap(texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glyph->texture = texture;
    glyph->width = face->glyph->bitmap.width;
    glyph->height = face->glyph->bitmap.rows;
    glyph->bearingx = face->glyph->bitmap_left;
    glyph->bearingy = face->glyph->bitmap_top;
    glyph->advance = face->glyph->advance.x;

    return AURA_SUCCESS;
}

int font_InitMesh(aura_Font_t* font)
{
    glGenVertexArrays(1, &font->mesh.VAO);
    glGenBuffers(1, &font->mesh.VBO);
    glBindVertexArray(font->mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, font->mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4,
                   NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT,
                     GL_FALSE, 4*sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return AURA_SUCCESS;
}

int aura_InitFont(const char* filename, int pixel_height, aura_Font_t* font)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        printf("Error: could not init freetype.\n");
        return AURA_FAILURE;
    }

    FT_Face face;
    if (FT_New_Face(ft, filename, 0, &face))
    {
        printf("Error: could not load font.\n");
        return AURA_FAILURE;
    }

    FT_Set_Pixel_Sizes(face, 0, pixel_height);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    for (unsigned char c = 0; c < 128; ++c)
    {
        font_InitGlyph(face, c, &font->glyphs[c]);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    if (font_InitMaterial(font) == AURA_FAILURE)
    {
        printf("Error: could not init shader program for %s.\n", filename);
        return AURA_FAILURE;
    }
    
    if (font_InitMesh(font) == AURA_FAILURE)
    {
        printf("Error: could not init mesh for %s.\n", filename);
        return AURA_FAILURE;
    }

    mat4 projection;

    return AURA_SUCCESS;
}

void aura_SetFontProjection(float left, float right,
                           float bottom, float top,
                           float near, float far, aura_Font_t* font)
{
    mat4 projection;
    glm_ortho(left, right, bottom, top, near, far, projection);
    aura_SetProgramUniform_Mat4(font->material.program, "projection", projection);
}

void aura_DrawText(const char* text, float x, float y, float scale, vec3 color,
                   aura_Font_t* font)
{
    glActiveTexture(GL_TEXTURE0);
    for (int i = 0; i < strlen(text); ++i)
        {
            aura_Glyph_t g = font->glyphs[text[i]];
            float xpos = x + g.bearingx * scale;
            float ypos = y + (g.height - g.bearingy) * scale;

            float w =  g.width * scale;
            float h =  g.height * scale;
            // update VBO for each character
            float vertices[6][4] = 
            {
                { xpos,     ypos - h,   0.0f, 0.0f },
                { xpos,     ypos ,      0.0f, 1.0f },
                { xpos + w, ypos ,      1.0f, 1.0f },

                { xpos,     ypos - h,   0.0f, 0.0f },
                { xpos + w, ypos ,      1.0f, 1.0f },
                { xpos + w, ypos - h,   1.0f, 0.0f }
            };

            glUseProgram(font->material.program);
            glBindVertexArray(font->mesh.VAO);
            glBindTexture(GL_TEXTURE_2D, g.texture);
            glBindBuffer(GL_ARRAY_BUFFER, font->mesh.VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (g.advance >> 6) * scale;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
}

void aura_SetFontColor(vec3 color, aura_Font_t* font)
{
    aura_SetProgramUniform_3f(font->material.program, "textcolor", color[0], color[1], color[2]);
}

void aura_CloseFont(aura_Font_t* font)
{
    glDeleteProgram(font->material.program);
    glDeleteBuffers(1, &font->mesh.VBO);
    glDeleteVertexArrays(1, &font->mesh.VAO);
}

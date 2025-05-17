#include "aura.h"

void glyph_Init(FT_Face face, unsigned char c, aura_Glyph* glyph)
{
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
        printf("Error loading character %c.\n", c);
        return;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glyph->texture = texture;
    glyph->w = face->glyph->bitmap.width;
    glyph->h = face->glyph->bitmap.rows;
    glyph->bearingx = face->glyph->bitmap_left;
    glyph->bearingy = face->glyph->bitmap_top;
    glyph->advance = face->glyph->advance.x;
}

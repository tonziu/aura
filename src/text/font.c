#include "aura.h"

void font_InitGlyphs(aura_Font* font)
{
    for (unsigned char c = 0; c < AURA_MAX_GLYPHS; ++c)
    {
        glyph_Init(font->face, c, &font->glyphs[c]); 
    }

    FT_Done_Face(font->face);
}

int font_Init(const char* filename, FT_Library ft, aura_Font* font)
{
    if (FT_New_Face(ft, filename, 0, &font->face))
    {
        return AURA_ERROR;
    }

    FT_Set_Pixel_Sizes(font->face, 0, 48);

    font_InitGlyphs(font);

    return AURA_OK;
}

#include "aura.h"
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int utils_ReadTextFile(const char* filename, char* buffer, int len)
{
    FILE* f;
    if (fopen_s(&f, filename, "rb") != 0) return AURA_ERROR;
    int read = fread(buffer, sizeof(char), len-1, f);
    buffer[read] = '\0';
    return AURA_OK;
}

int utils_LoadImage(const char* filename, GLFWimage* image)
{
    image->pixels = stbi_load(filename, &image->width, 
                                        &image->height, 
                                        0, STBI_rgb_alpha);
    if (!image->pixels)
    {
        printf("Error: Could not load image %s\n", filename);
        return AURA_ERROR;
    }

    return AURA_OK;
}

void utils_FreeImage(GLFWimage* image)
{
    stbi_image_free(image->pixels);
}

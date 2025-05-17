#include "aura.h"
#include <stdio.h>

int utils_ReadTextFile(const char* filename, char* buffer, int len)
{
    FILE* f;
    if (fopen_s(&f, filename, "rb") != 0) return AURA_ERROR;
    int read = fread(buffer, sizeof(char), len-1, f);
    buffer[read] = '\0';
    return AURA_OK;
}

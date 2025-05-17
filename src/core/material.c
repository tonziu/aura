#include "aura.h"
#include <stdio.h>

int material_CompileShader(const char* src, GLenum type, GLuint* shader)
{
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &src, 0);
    glCompileShader(*shader);
    int compiled;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        char infolog[512];
        glGetShaderInfoLog(*shader, 512, 0, infolog);
        printf("%s\n", infolog);
        return AURA_ERROR;
    }

    return AURA_OK;
}

int material_LinkProgram(const char* vsrc, const char* fsrc,
                         aura_Material* material)
{
    int ret = AURA_OK;
    GLuint vshader, fshader;
    material->program = glCreateProgram();
    ret = material_CompileShader(vsrc, GL_VERTEX_SHADER, &vshader);
    if (ret == AURA_ERROR) return AURA_ERROR;

    ret = material_CompileShader(fsrc, GL_FRAGMENT_SHADER, &fshader);
    if (ret == AURA_ERROR) return AURA_ERROR;

    glAttachShader(material->program, vshader);
    glAttachShader(material->program, fshader);
    glLinkProgram(material->program);

    int linked;
    glGetProgramiv(material->program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        char infolog[512];
        glGetProgramInfoLog(material->program, 512, 0, infolog);
        printf("%s\n", infolog);
        return AURA_ERROR;
    }

    return AURA_OK;
}

int material_InitProgram(const char* vs_path, 
                          const char* fs_path, aura_Material* material)
{
    char vsrc[512];
    char fsrc[512];
    if (utils_ReadTextFile(vs_path, vsrc, 512) == AURA_ERROR)
    {
        return AURA_ERROR;
    }
    if (utils_ReadTextFile(fs_path, fsrc, 512) == AURA_ERROR)
    {
        return AURA_ERROR;
    }

    int ret = material_LinkProgram(vsrc, fsrc, material);
    return ret;
}

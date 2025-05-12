#include "aura.h"
#include <stdio.h>

int aura_CompileShader(const char* src, GLenum type, GLuint* shader)
{
    *shader = glCreateShader(type);
    
    glShaderSource(*shader, 1, &src, NULL);
    glCompileShader(*shader); 
    GLint compiled;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        char infolog[512];
        glGetShaderInfoLog(*shader, 512, NULL, infolog);
        fprintf(stdout, "Error: could not compile shader of type %d:\n%s\n", type, infolog);
        glDeleteShader(*shader);
        return AURA_FAILURE;
    }
    return AURA_SUCCESS;
}

int aura_LinkProgram(GLuint vshader, GLuint fshader, GLuint* program)
{
    *program = glCreateProgram();
    glAttachShader(*program, vshader);
    glAttachShader(*program, fshader);
    glLinkProgram(*program);
    GLint linked;
    glGetProgramiv(*program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        char infolog[512];
        glGetProgramInfoLog(*program, 512, NULL, infolog);
        fprintf(stdout, "Error: could not link program using shaders %d and %d:\n%s\n", vshader, fshader, infolog);
        glDeleteProgram(*program);
        return AURA_FAILURE;
    }
    glDeleteShader(vshader);
    glDeleteShader(fshader);
    return AURA_SUCCESS;
}

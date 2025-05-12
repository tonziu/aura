#include "aura.h"
#include <stdio.h>

int main(void)
{
    aura_Window_t window; // We need a window (and an OpenGL context) to use shaders
    if (aura_InitWindow(600, 400, "Shader compilation", &window) == AURA_FAILURE)
    {
        printf("Error: could not initialize window.\n");
        return 1;
    }

    const char* vshader_src = 
        "#version 330 core\n"
        "layout(location = 0) in vec2 aPos;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
        "}\0";

    const char* fshader_src = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(1.0f);\n"
        "}\0";

    GLuint vshader, fshader;
    if (aura_CompileShader(vshader_src, GL_VERTEX_SHADER, &vshader) == AURA_FAILURE)
    {
        printf("Error: could not compile shader of type %d.\n", GL_VERTEX_SHADER); 
        return 1;
    }
    
    if (aura_CompileShader(fshader_src, GL_FRAGMENT_SHADER, &fshader) == AURA_FAILURE)
    {
        printf("Error: could not compile shader of type %d.\n", GL_FRAGMENT_SHADER); 
        return 1;
    }

    GLuint program;
    if (aura_LinkProgram(vshader, fshader, &program) == AURA_FAILURE)
    {
        printf("Error: could not link program using %d and %d.\n", vshader, fshader);
        return 1;
    }

    printf("Successfully compiled shaders %d and %d.\n", vshader, fshader);
    printf("Successfully linked program %d.\n", program);

    return 0;
}

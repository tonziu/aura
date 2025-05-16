#include <stdio.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"

#define ERROR 1
#define OKAY 0

int shader_CompileSource(const char* src, GLenum type, GLuint* shader)
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
        fprintf(stderr, "Error: could not compile %d:\n%s\n",
                        *shader, infolog);
        return ERROR;
    }

    return OKAY;
}

int program_Link(GLuint vshader, GLuint fshader, GLuint* program)
{
    *program = glCreateProgram();
    glAttachShader(*program, vshader);
    glAttachShader(*program, fshader);
    glLinkProgram(*program);
    int linked;
    glGetProgramiv(*program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        char infolog[512];
        glGetProgramInfoLog(*program,  512, 0, infolog);
        fprintf(stderr, "Error: could not link %d:\n%s\n",
                        *program, infolog);
        return ERROR;
    }
    
    glDeleteShader(vshader);
    glDeleteShader(fshader);

    return OKAY;
}

int program_UniformMat4(GLuint program, const char* name, mat4 data)
{
    glUseProgram(program);
    GLint loc;
    loc = glGetUniformLocation(program, name);
    if (loc == -1) return ERROR;
    glUniformMatrix4fv(loc, 1, 0, &data[0][0]);
    return OKAY;
}

int program_UniformVec4(GLuint program, const char* name, vec4 data)
{
    glUseProgram(program);
    GLint loc;
    loc = glGetUniformLocation(program, name);
    if (loc == -1) return ERROR;
    glUniform4fv(loc, 1, data);
    return OKAY;
}

typedef struct
{
    GLuint vao;
    GLuint vbo;
} Mesh;

typedef struct
{
    GLuint program;
} Material;

Mesh mesh_Rectangle()
{
    Mesh m;
    glGenVertexArrays(1, &m.vao);
    glGenBuffers(1, &m.vbo);
    glBindVertexArray(m.vao);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);

    float vertices[8] = 
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return m;
}

Material material_FromShaders(const char* vsrc, const char* fsrc)
{
    Material m;
    GLuint vshader, fshader;
    shader_CompileSource(vsrc, GL_VERTEX_SHADER, &vshader);
    shader_CompileSource(fsrc, GL_FRAGMENT_SHADER, &fshader);
    program_Link(vshader, fshader, &m.program);
    return m;
}

typedef struct
{
    float x;
    float y;
    float w;
    float h;
} Rectangle;

Material material_Rectangle(Rectangle viewport)
{
    const char* vsrc =
        "#version 330 core\n"
        "layout(location = 0) in vec2 pos;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 model;\n"
        "void main() {\n"
        "   gl_Position = projection * model * vec4(pos, 0, 1);\n"
        "}\0";
    
    const char* fsrc =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 fillcolor;\n"
        "void main() {\n"
        "   FragColor = fillcolor;\n"
        "}\0";

    Material m = material_FromShaders(vsrc, fsrc);
    mat4 projection;
    glm_ortho(viewport.x, 
              viewport.x + viewport.w, 
              viewport.y + viewport.h, 
              viewport.y, -1, 1, projection);
    program_UniformMat4(m.program, "projection", projection);
    return m;
}

typedef struct
{
    Mesh rect_mesh;
    Material rect_material;
} Renderer;

void renderer_Init(Renderer* renderer, int screen_width, int screen_height)
{
    Rectangle viewport = {0, 0, screen_width, screen_height};
    renderer->rect_material = material_Rectangle(viewport);
    renderer->rect_mesh = mesh_Rectangle();
}

void renderer_DrawRectangle(Renderer* renderer, Rectangle rectangle, vec4 color)
{
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    vec3 translation = {rectangle.x, rectangle.y, 0.0f}; 
    vec3 scaling = {rectangle.w, rectangle.h, 1.0f};
    glm_translate(model, translation);
    glm_scale(model, scaling);
    program_UniformMat4(renderer->rect_material.program, "model", model);
    program_UniformVec4(renderer->rect_material.program, "fillcolor", color);
    glUseProgram(renderer->rect_material.program);
    glBindVertexArray(renderer->rect_mesh.vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}

int main(void)
{
    // ------------------------------------------------------------
    // OPENGL Context Creation
    // ------------------------------------------------------------
    
    if (!glfwInit()) return ERROR;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(1000, 800, "Pong", NULL, NULL);
    if (!window) return ERROR;

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) return ERROR;

    glViewport(0, 0, 1000, 800);

    // ------------------------------------------------------------


    // My objects
    // ------------------------------------------------------------
    
    // To render an entity, we need to know:
    //  1. What to render (mesh)
    //  2. How to render it (material)
    
    Renderer renderer;
    renderer_Init(&renderer, 1000, 800);
    Rectangle rect = {400, 400, 100, 100};
    vec4 color = {1, 1, 0, 1};
    
    // ------------------------------------------------------------
     
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.12, 0.12, 0.18, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer_DrawRectangle(&renderer, rect, color);

        glfwPollEvents();
        glfwSwapBuffers(window);
        glFinish();
    }

    glfwTerminate();

    return 0;
}

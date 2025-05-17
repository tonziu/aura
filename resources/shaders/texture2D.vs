#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texcoords;
out vec2 TexCoords;
uniform mat4 projection;
uniform mat4 model;
void main()
{
    gl_Position = projection * model * vec4(pos, 0, 1);
    TexCoords = texcoords;
}

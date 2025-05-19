#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex_coords;
out vec2 TexCoords;
uniform mat4 projection;
uniform mat4 model;
uniform float rows;
uniform float cols;
uniform float row;
uniform float frame;
void main() {
    vec2 frame_size = vec2(1.0 / cols, 1.0 / rows);
    float col = mod(frame, cols);
    vec2 offset = vec2(col, row) * frame_size;
    TexCoords = tex_coords * frame_size + offset;
    gl_Position = projection * model * vec4(pos, 0, 1);
}

#version 420

layout (location = 0) in vec2 in_position;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_texture;

layout (location = 3) in vec3 in_transform1;
layout (location = 4) in vec3 in_transform2;
layout (location = 5) in vec3 in_transform3;
layout (location = 6) in vec3 in_transform4;

uniform mat4 projection;

out vec3 ex_color;
out vec2 ex_texture;

void main()
{
    mat4 model;
    model[0] = vec4(in_transform1, 0.0f);
    model[1] = vec4(in_transform2, 0.0f);
    model[2] = vec4(in_transform3, 0.0f);
    model[3] = vec4(in_transform4, 1.0f);

    gl_Position =  projection * model * vec4(in_position.x, in_position.y, 0.0, 1.0);
    ex_color = in_color;
    ex_texture = in_texture;
}

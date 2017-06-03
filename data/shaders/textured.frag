#version 420

in vec3 ex_color;
in vec2 ex_texture;

out vec4 out_color;

uniform sampler2D u_texture;

void main()
{
    out_color = texture(u_texture, ex_texture) * vec4(ex_color, 1.0);
}

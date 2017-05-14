#version 330

in vec3 out_color;
out vec4 vertex_color;

void main() 
{
    vertex_color = vec4(out_color.x, out_color.y, out_color.z, 1.0f);
}


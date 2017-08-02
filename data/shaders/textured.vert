#version 420

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inOffset;
layout (location = 2) in vec2 inTexture;
layout (location = 3) in vec2 inSize;

out vec3 outColor;
out vec2 outTexture;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4((inPos * inSize) + inOffset, 0.0, 1.0);
    outColor = vec3(1.0, 1.0, 1.0);
    outTexture = inTexture;
}

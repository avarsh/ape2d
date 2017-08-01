#version 420

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inOffset;
layout (location = 2) in vec2 inTexture;

out vec3 outColor;
out vec2 outTexture;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(inPos + inOffset, 0.0, 1.0);
    outColor = vec3(1.0, 0.7, 0.2);
    outTexture = inTexture;
}

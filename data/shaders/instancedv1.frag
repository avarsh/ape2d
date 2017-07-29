#version 420

in vec3 outColor;
in vec2 outTexture;

out vec4 exColor;

uniform sampler2D tex;

void main()
{
    exColor = texture(tex, outTexture) * vec4(outColor, 1.0);
}

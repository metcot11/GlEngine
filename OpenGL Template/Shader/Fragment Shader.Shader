#version 330 core

out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;


uniform sampler2D  mTexture1;
uniform sampler2D  mTexture2;
uniform float scrol;

void main()
{
    FragColor = mix(texture(mTexture1, TexCoord), texture(mTexture2, TexCoord), scrol);
} 
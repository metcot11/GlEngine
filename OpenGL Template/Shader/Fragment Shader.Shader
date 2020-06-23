#version 330 core

out vec4 FragColor;


in vec2 TexCoord;


uniform sampler2D  mTexture0;
uniform sampler2D  mTexture1;
uniform float scrol;

void main()
{
    FragColor = mix(texture(mTexture0, TexCoord), texture(mTexture1, TexCoord), scrol);
} 
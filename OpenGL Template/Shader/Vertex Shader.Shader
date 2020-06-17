#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTextCoord;

out vec3 Color;
out vec2 TexCoord;
out vec2 TexCoord2;

uniform mat4 Transform;

void main()
{
	gl_Position = Transform * vec4(aPos, 1.0);
	Color = aColor;
	TexCoord = aTextCoord;
}
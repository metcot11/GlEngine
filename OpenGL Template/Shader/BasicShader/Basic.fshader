#version 330 core

out vec4 FragColor;

in vec2 TextureCoord;
in vec3 Normal;
in vec3 Position;

uniform sampler2D Texture;
uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform bool tex;

void main()
{
	if(tex){
		vec3 I		= normalize(Position - cameraPos);
		vec3 R		= reflect(I, normalize(Normal));
		FragColor	= vec4(texture(skybox, R).rgb, 1.0);
	}else{
		FragColor		= vec4(texture(Texture, TextureCoord).rgb, 1.0);
	}
}
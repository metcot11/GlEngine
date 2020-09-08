#include "Texture.h"

#include "stb.h"
#include <string>

Texture::Texture()
	:TextureId(0), textureName("texture")
{
	glGenTextures(1, &TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1240, 640, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const char* filePath, const char* Name, bool flip)
	:textureName(Name)
{

	unsigned int texture;
	int width, height, nrChannels = 0;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	TextureId = texture;

	stbi_set_flip_vertically_on_load(flip);
	unsigned char* Data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (Data)
	{
		GLenum format = GL_RGB;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, Data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load Texture at" << filePath << std::endl;
		__debugbreak();
	}
	stbi_image_free(Data);

}

Texture::~Texture()
{
}

void Texture::operator=(Texture t)
{
	this->TextureId = t.TextureId;
	this->textureName = t.textureName;
	this->Type = t.Type;
	this->path = t.Type;
}

void Texture::LoadTexture2D(const char* filePath, bool flip)
{
	unsigned int texture;
	int width, height, nrChannels;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	TextureId = texture;
	stbi_set_flip_vertically_on_load(flip);
	unsigned char* Data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (Data)
	{
		GLenum format = GL_RGB;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, Data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load Texture at: " << filePath << std::endl;
		__debugbreak();
	}
	stbi_image_free(Data);
}

void Texture::BindTexture2D(Shader shade, int slot)
{
	shade.SetUniformInt(textureName, slot);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, TextureId);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, TextureId);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

CubeMap::CubeMap(std::vector<const char*> filePaths)
{
	glGenTextures(1, & CubeMapId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapId);
	
	int width, height, nrChannels;
	unsigned char* data;

	for (unsigned int i = 0; i < filePaths.size(); i++) {
		data = stbi_load(filePaths[i], &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cout << "Failed to load CubeMap: " << filePaths[i] << '\n';
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

CubeMap::CubeMap()
{
	glGenTextures(1, &CubeMapId);
}

CubeMap::~CubeMap()
{
}

void CubeMap::LoadTextures(std::vector<const char*> filePaths)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapId);
	int width, height, nrChannels;
	unsigned char* data;

	for (unsigned int i = 0; i < filePaths.size(); i++) {
		data = stbi_load(filePaths[i], &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cout << "Failed to load CubeMap: " << filePaths[i] << '\n';
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void CubeMap::BindCubeMap(Shader s, int slot)
{
	s.SetUniformInt("skybox", slot);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapId);
}

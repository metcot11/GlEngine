#include "Texture.h"

#include "stb.h"
#include <string>

Texture::Texture(Shader s)
	:shade(s)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(Shader s, const char* filePath, const char* Id, GLenum format)
	:shade(s)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int texture;
	int width, height, nrChannels;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	TextureMap.insert({ Id, texture });


	unsigned char* Data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(true);
	if (Data)
	{
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

void Texture::CreateTexture2D(const char* filePath, const char* Id, GLenum format)
{
	unsigned int texture;
	int width, height, nrChannels;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	TextureMap.insert({ Id, texture });

	unsigned char* Data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(true);
	if (Data)
	{
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

void Texture::BindTexture2D(const char* Id, int slot)
{
	std::string tex = "mTexture" + std::to_string(slot);
	shade.SetUniformInt(tex.c_str(), slot);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, TextureMap[Id]);
}
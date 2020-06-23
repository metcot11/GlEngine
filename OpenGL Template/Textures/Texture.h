#pragma once
#include <glew.h>

#include "Shader.h"

#include <unordered_map>
#include <iostream>

class Texture
{
private:
	Shader shade;
	std::unordered_map<const char*, unsigned int> TextureMap;

public:
	Texture(Shader s);
	Texture(Shader s, const char* filePath, const char* Id, GLenum format);
	~Texture();

	void CreateTexture2D(const char* filePath, const char* Id, GLenum format);
	void BindTexture2D(const char* Id, int slot);
};
#pragma once
#include <glew.h>

#include "Shader.h"

#include <unordered_map>
#include <string>
#include <iostream>

void FlipTextures();

class Texture
{
public:
	unsigned int TextureId;
	const char* textureName;

	std::string Type;
	std::string path;

	Texture();
	Texture(const char* filePath, const char* Name);
	~Texture();

	void LoadTexture2D(const char* filePath);
	void BindTexture2D(Shader shade, int slot);
};
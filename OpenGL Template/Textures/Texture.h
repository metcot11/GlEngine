#pragma once
#include <glew.h>

#include "Shader.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

class Texture
{
public:
	unsigned int TextureId;
	const char* textureName;

	std::string Type;
	std::string path;

	Texture();
	Texture(const char* filePath, const char* Name, bool flip);
	~Texture();

	void LoadTexture2D(const char* filePath, bool flip);
	void BindTexture2D(Shader shade, int slot);
};
class CubeMap {
public:
	unsigned int CubeMapId;

	CubeMap(std::vector<const char*> filePaths);
	~CubeMap();

	void BindCubeMap(Shader s, int slot);
};
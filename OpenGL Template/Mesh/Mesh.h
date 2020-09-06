#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Textures/Texture.h"

#include <vector>
#include <string>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

class Mesh
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

public:
	std::vector<Vertex>			mVertices;
	std::vector<unsigned int>	mIndices;
	std::vector<Texture>		mTextures;

	Mesh(std::vector<Vertex> ver, std::vector<unsigned int> ind, std::vector<Texture> tex);
	~Mesh();
	
	void Draw(Shader& shader, glm::vec3 pos);
	void Draw(Shader& shader);

private:
	void SetupMesh();
};


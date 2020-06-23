#pragma once
#include <glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "BufferObject.h"

#include "Camera/Camera.h"

class Renderer
{
private:

	BufferObject Buffer;
	Shader Shade;
	Camera& Mouse;
public:
	Renderer(Shader s, Camera& m);
	~Renderer();

	void GenCube(float* Vertices, int Datasize, unsigned int* Indices, int Indsize);

	void RenderCube(glm::vec3 Pos);
	void RenderRotatingCube(glm::vec3 Pos, float angle);

	void GenSquare(float* Vertices, int Datasize, unsigned int* Indices, int Indsize);
	void RenderSquare(glm::vec3 Pos);
};


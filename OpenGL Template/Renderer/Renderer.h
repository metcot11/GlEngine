#pragma once
#include <glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "BufferObject.h"
#include "data.h"

#include "Lighting.h"
#include "Camera/Camera.h"

class Renderer
{
private:
	const char* BufferDataId;

	BufferObject Buffer;
	Camera& Mouse;
	Shader Shade;
public:
	Renderer(Shader s, Camera& m);
	~Renderer();

	void GenCube(const char* CubeId);
	void GenLightCube(const char* LightCubeId);
	void GenTestScene1();

	void RenderCube(glm::vec3 Pos, const char* CubeId, Shader s );
	void RenderLightCube(glm::vec3 Pos, const char* LightCubeId, Shader s, PointLight p);

};


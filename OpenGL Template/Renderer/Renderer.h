#pragma once
#include <glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "BufferObject.h"
#include "Textures/Texture.h"
#include "data.h"

#include "Lighting.h"
#include "Camera/Camera.h"

class Renderer
{
private:
	const char* CubeBufferDataId;
	const char* PlaneBufferDataId;

	BufferObject Buffer;
	Camera& camera;
public:
	Renderer(Camera& m);
	~Renderer();

	void GenCube(const char* CubeId);
	void GenLightCube(const char* LightCubeId);
	void GenPlane(const char* Id);
	void GenTestScene1();

	void RenderPlane(const char* Id, Shader s, Texture t);
	void RenderCube(glm::vec3 Pos, const char* CubeId, Shader s, Texture t);
	void RenderLightCube(glm::vec3 Pos, const char* LightCubeId, Shader s, PointLight p);

};


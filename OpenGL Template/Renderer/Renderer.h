#pragma once
#include <glew.h>
#include <vector>

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
	Camera& camera;
	Shader r_BasicShader;

	/* ----------Box---------- */
	BufferObject r_BoxBuffer;
	Texture r_BoxTexture;
	/* ----------Plane---------- */
	BufferObject r_PlaneBuffer;
	Texture r_PlaneTexture;
	/* ----------SkyBox---------- */
	Shader r_SkyShader;
	BufferObject r_SkyBuffer;
	CubeMap r_Skybox;
	/* ----------Quad---------- */
	Shader r_QuadShader;
	BufferObject r_QuadBuffer;
	FrameBuffer r_FrameBuffer;
public:
	Renderer(Camera& m);
	~Renderer();

	void UpdateFrame();

	void UpdateInput();
	void DrawScene();
private:
	void DrawCube(Shader shader, CubeMap texture, BufferObject& Buffer, glm::vec3 pos, float f);
	void DrawPlane(Shader shader, Texture texture, BufferObject& Buffer, glm::vec3 pos);
	void DrawSkyBox(Shader shader, CubeMap Skybox, BufferObject& Buffer);
};


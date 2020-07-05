#include "Renderer.h"


Renderer::Renderer(Shader s, Camera& m)
	:Shade(s), Mouse(m)
{
	Buffer.CreateVertexBuffer(sizeof(vertices), vertices, BufferDataId);
}

Renderer::~Renderer()
{
}

void Renderer::GenCube(const char* CubeId)
{
	Buffer.CreateVertexArrayBuffer(CubeId);
	Buffer.BindVertexArrayBuffer(CubeId);
	Buffer.BindVertexBuffer(BufferDataId);
	Buffer.AttribPointer(0, 3, GL_FLOAT, 8, 0);
	Buffer.AttribPointer(1, 3, GL_FLOAT, 8, 3);
	Buffer.AttribPointer(2, 2, GL_FLOAT, 8, 6);
	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
}

void Renderer::GenLightCube(const char* LightCubeId)
{
	Buffer.CreateVertexArrayBuffer(LightCubeId);
	Buffer.BindVertexArrayBuffer(LightCubeId);
	Buffer.BindVertexBuffer(BufferDataId);
	Buffer.AttribPointer(0, 3, GL_FLOAT, 8, 0);
	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
}

void Renderer::GenTestScene1()
{
}

void Renderer::RenderCube(glm::vec3 Pos, const char* CubeId, Shader s)
{
	s.On();
	Buffer.BindVertexBuffer(BufferDataId);
	Buffer.BindVertexArrayBuffer(CubeId);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, Pos);
	glm::mat3 Trans_Normal = glm::inverse(glm::transpose(model));

	s.SetUniformMat4("model", model);
	s.SetUniformMat3("Trans_Normal", Trans_Normal);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
	s.Off();
}

void Renderer::RenderLightCube(glm::vec3 Pos, const char* LightCubeId, Shader s, PointLight pointLight)
{
	s.On();
	Buffer.BindVertexBuffer(BufferDataId);
	Buffer.BindVertexArrayBuffer(LightCubeId);

	pointLight.RenderPntLight(Pos, s);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, Pos);
	model = glm::scale(model, glm::vec3(0.2f));
	s.SetUniformMat4("model", model);
	s.SetUniformVec3("color", pointLight.ambient);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
	s.Off();
}



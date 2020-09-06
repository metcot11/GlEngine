#include "Renderer.h"


Renderer::Renderer(Camera& m)
	:camera(m), CubeBufferDataId(0), PlaneBufferDataId(0)
{
}

Renderer::~Renderer()
{
}
#ifdef DEBUG
void Renderer::GenCube(const char* CubeId)
{
	Buffer.CreateVertexBuffer(sizeof(vertices), vertices, CubeBufferDataId);
	Buffer.CreateVertexArrayBuffer(CubeId);
	Buffer.BindVertexArrayBuffer(CubeId);
	Buffer.BindVertexBuffer(CubeBufferDataId);
	Buffer.AttribPointer(0, 3, GL_FLOAT, 8, 0);
	Buffer.AttribPointer(1, 3, GL_FLOAT, 8, 3);
	Buffer.AttribPointer(2, 2, GL_FLOAT, 8, 6);
	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
}

void Renderer::GenLightCube(const char* LightCubeId)
{
	Buffer.CreateVertexBuffer(sizeof(vertices), vertices, CubeBufferDataId);
	Buffer.CreateVertexArrayBuffer(LightCubeId);
	Buffer.BindVertexArrayBuffer(LightCubeId);
	Buffer.BindVertexBuffer(CubeBufferDataId);
	Buffer.AttribPointer(0, 3, GL_FLOAT, 8, 0);
	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
}

void Renderer::GenPlane(const char* Id)
{
	Buffer.CreateVertexBuffer(sizeof(PlaneData), PlaneData, PlaneBufferDataId);

	Buffer.CreateVertexArrayBuffer(Id);
	Buffer.BindVertexArrayBuffer(Id);
	Buffer.BindVertexBuffer(PlaneBufferDataId);

	Buffer.AttribPointer(0, 3, GL_FLOAT, 5, 0);
	Buffer.AttribPointer(1, 2, GL_FLOAT, 5, 3);

	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
}

void Renderer::GenTestScene1()
{
}

void Renderer::RenderPlane(const char* Id, Shader s, Texture t)
{
	Buffer.BindVertexBuffer(PlaneBufferDataId);
	Buffer.BindVertexArrayBuffer(Id);

	s.SetUniformMat4("model", glm::mat4(1.0f));
	t.BindTexture2D(s, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
}

void Renderer::RenderCube(glm::vec3 Pos, const char* CubeId, Shader s, Texture t)
{
	s.On();
	Buffer.BindVertexBuffer(CubeBufferDataId);
	Buffer.BindVertexArrayBuffer(CubeId);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, Pos);
	glm::mat3 Trans_Normal = glm::inverse(glm::transpose(model));

	s.SetUniformMat4("model", model);
	s.SetUniformMat3("Trans_Normal", Trans_Normal);
	t.BindTexture2D(s, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
	s.Off();
}

void Renderer::RenderLightCube(glm::vec3 Pos, const char* LightCubeId, Shader s, PointLight pointLight)
{
	s.On();
	Buffer.BindVertexBuffer(CubeBufferDataId);
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
#endif // DEBUG


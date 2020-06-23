#include "Renderer.h"


Renderer::Renderer(Shader s, Camera& m)
	:Shade(s), Mouse(m)
{
}

Renderer::~Renderer()
{
}

void Renderer::GenCube(float* Vertices, int Datasize, unsigned int* Indices, int Indsize )
{
	Buffer.CreateVertexBuffer(Datasize, Vertices, "Cube");
	Buffer.BindVertexBuffer("Cube");

	Buffer.CreateElementBuffer(Indsize, Indices, "IndCube");
	Buffer.BindElementBuffer("IndCube");

	Buffer.CreateVertexArrayBuffer("VaoCube");
	Buffer.BindVertexArrayBuffer("VaoCube");
	Buffer.AttribPointer(0, 3, GL_FLOAT, 5, 0);
	Buffer.AttribPointer(1, 2, GL_FLOAT, 5, 3);

	Buffer.UnBindVertexArrayBuffer();
}

void Renderer::RenderCube(glm::vec3 Pos)
{
	Buffer.BindVertexArrayBuffer("VaoCube");

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, Pos);
	model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
	Shade.SetUniformMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::RenderRotatingCube(glm::vec3 Pos, float angle)
{
	Buffer.BindVertexArrayBuffer("VaoCube");

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, Pos);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	Shade.SetUniformMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::GenSquare(float* Vertices, int Datasize, unsigned int* Indices, int Indsize)
{
	Buffer.CreateVertexBuffer(Datasize, Vertices, "square");
	Buffer.BindVertexBuffer("square");

	Buffer.CreateElementBuffer(Indsize, Indices, "Indsquare");
	Buffer.BindElementBuffer("Indsquare");

	Buffer.CreateVertexArrayBuffer("Vaosquare");
	Buffer.BindVertexArrayBuffer("Vaosquare");

	Buffer.AttribPointer(0, 3, GL_FLOAT, 8, 0);
	Buffer.AttribPointer(0, 3, GL_FLOAT, 8, 3);
	Buffer.AttribPointer(0, 3, GL_FLOAT, 8, 6);

	Buffer.UnBindVertexArrayBuffer();
}

void Renderer::RenderSquare(glm::vec3 Pos)
{

}


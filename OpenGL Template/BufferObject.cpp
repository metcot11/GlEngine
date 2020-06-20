#include "BufferObject.h"



BufferObject::BufferObject()
{
}


BufferObject::~BufferObject()
{
	for (auto& i : VertexArrayObjectId)
	{
		glDeleteVertexArrays(1, &i.second);
	}
	for (auto& i : VertexBufferObjectId)
	{
		glDeleteBuffers(1, &i.second);
	}
	for (auto& i : ElementBufferObjectId)
	{
		glDeleteBuffers(1, &i.second);
	}
}

void BufferObject::CreateVertexBuffer(int size,const void* Data, const char* Id)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, Data, GL_STATIC_DRAW);

	VertexBufferObjectId.insert({Id, VBO});
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferObject::CreateElementBuffer(int size, const void* Data, const char* Id)
{
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, Data, GL_STATIC_DRAW);

	ElementBufferObjectId.insert({ Id, EBO });
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BufferObject::CreateVertexArrayBuffer(const char* Id)
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	VertexArrayObjectId.insert({ Id,VAO });
}

void BufferObject::Bind(const char* EBO, const char* VBO, const char* VAO)
{
	if (VertexArrayObjectId.find(VAO) == VertexArrayObjectId.end())
	{
		std::cout << "Vertex Array not found!" << '\n';
		__debugbreak();
	}
	else {
		glBindVertexArray(VertexArrayObjectId[VAO]);
	}
	if (VertexBufferObjectId.find(VBO) == VertexBufferObjectId.end())
	{
		std::cout << "Vertex Buffer not found!" << '\n';
		__debugbreak();
	}
	else {
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObjectId[VBO]);
	}
	if (ElementBufferObjectId.find(EBO) == ElementBufferObjectId.end())
	{
		std::cout << "Element Buffer not found!" << '\n';
		__debugbreak();
	}
	else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObjectId[EBO]);
	}
}

void BufferObject::BindVertexBuffer(const char* VBO)
{
	if (VertexBufferObjectId.find(VBO) == VertexBufferObjectId.end())
	{
		std::cout << "Vertex Buffer not found!" << '\n';
		__debugbreak();
	}
	else {
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObjectId[VBO]);
	}
}

void BufferObject::BindElementBuffer(const char* EBO)
{
	if (ElementBufferObjectId.find(EBO) == ElementBufferObjectId.end())
	{
		std::cout << "Element Buffer not found!" << '\n';
		__debugbreak();
	}
	else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObjectId[EBO]);
	}
}

void BufferObject::BindVertexArrayBuffer(const char* VAO)
{
	if (VertexArrayObjectId.find(VAO) == VertexArrayObjectId.end())
	{
		std::cout << "Vertex Array not found!" << '\n';
		__debugbreak();
	}
	else {
		glBindVertexArray(VertexArrayObjectId[VAO]);
	}
}

void BufferObject::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BufferObject::UnBindVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferObject::UnBindElementBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BufferObject::UnBindVertexArrayBuffer()
{
	glBindVertexArray(0);
}

void BufferObject::AttribPointer(int LayoutPos, int Size, GLenum type, int Stride, int Offset)
{
	glVertexAttribPointer(LayoutPos, Size, type, GL_FALSE, Stride * sizeof(float), (void*)(Offset*sizeof(float)));
	glEnableVertexAttribArray(LayoutPos);
}

void BufferObject::EnableVertexAtrrib(int LayoutPos)
{
	glEnableVertexAttribArray(LayoutPos);
}

void BufferObject::DisableVertexAttrib(int LayoutPos)
{
	glDisableVertexAttribArray(LayoutPos);
}

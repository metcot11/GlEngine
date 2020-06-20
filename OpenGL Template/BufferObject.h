#pragma once

#include <glew.h>

#include <iostream>
#include <unordered_map>

class BufferObject
{
private:
	std::unordered_map<const char*, int unsigned> VertexArrayObjectId;
	std::unordered_map<const char*, int unsigned> VertexBufferObjectId;
	std::unordered_map<const char*, int unsigned> ElementBufferObjectId;
public:
	BufferObject();
	~BufferObject();

	void CreateVertexBuffer(int size, const void* Data, const char* Id);
	void CreateElementBuffer(int size, const void* Data, const char* Id);
	void CreateVertexArrayBuffer(const char* Id);

	void Bind(const char* EBO, const char* VBO, const char* VAO);
	void BindVertexBuffer(const char* VBO);
	void BindElementBuffer(const char* EBO);
	void BindVertexArrayBuffer(const char* VAO);

	void UnBind();
	void UnBindVertexBuffer();
	void UnBindElementBuffer();
	void UnBindVertexArrayBuffer();

	void AttribPointer(int LayoutPos, int Size, GLenum type, int Stride, int Offset);
	void EnableVertexAtrrib(int LayoutPos);
	void DisableVertexAttrib(int LayoutPos);
};


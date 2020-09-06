#pragma once

#include <glew.h>
#include <iostream>

#include "Shader.h"
#include "data.h"

struct BufferLayout {
	GLenum Target;
	unsigned int Id;
	int Size;
	void* ptrMemory;
	bool MapStatus;

	BufferLayout(GLenum target, unsigned int id)
		:Target(target), Id(id), Size(0), 
		 ptrMemory(nullptr), MapStatus(false){}
	BufferLayout(GLenum target, unsigned int id, int size)
		:Target(target), Id(id), Size(size),
		ptrMemory(nullptr), MapStatus(false) {}
	BufferLayout(GLenum target, unsigned int id, int size, void* ptr)
		:Target(target), Id(id), Size(size),
		ptrMemory(ptr), MapStatus(true) {}
	~BufferLayout() = default;

	BufferLayout operator=(BufferLayout buffer)
	{
		return {buffer.Target, buffer.Id, buffer.Size};
	}
};

class BufferObject
{
private:
	BufferLayout m_VBO;		/*Vertex Buffer Object*/
	BufferLayout m_EBO;		/*Element Buffer Object*/
	BufferLayout m_VAO;		/*Vertex Array Object*/
public:
	BufferObject();
	BufferObject(int size, const void* Data);
	BufferObject(BufferLayout VBO, BufferLayout VAO, BufferLayout EBO );
	~BufferObject();

	BufferObject operator=(BufferObject buffer);

	BufferLayout& CreateVertexBuffer(int size, const void* Data);
	BufferLayout& CreateElementBuffer(int size, const void* Data);
	BufferLayout& CreateVertexArrayBuffer();

	void GenSubData(const void* data, int offset);
	void CopyBufferFrom(BufferLayout buffer, int readoffset, int writeoffset, int size);

	void BindBuffer(BufferLayout& layout);
	void BindBuffer();

	void UnBind();
	void UnBindVertexBuffer();
	void UnBindElementBuffer();
	void UnBindVertexArrayBuffer();

	void AttribPointer(int LayoutPos, int Size, GLenum type, int Stride, int Offset);
	void EnableVertexAtrrib(int LayoutPos);
	void DisableVertexAttrib(int LayoutPos);
};

class FrameBuffer 
{
private:
	unsigned int FrameId;
	unsigned int RenderId;
	unsigned int TextureId;

	BufferObject QuadBuffer;
	Shader QuadShader;
public:
	FrameBuffer();
	~FrameBuffer() = default;

	void Draw(void (*DrawCall)());
};



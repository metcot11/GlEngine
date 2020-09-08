#include "BufferObject.h"



BufferObject::BufferObject()
	:m_VAO({GL_VERTEX_ARRAY, 0}), 
	 m_VBO({GL_ARRAY_BUFFER, 0 }),
	 m_EBO({GL_ELEMENT_ARRAY_BUFFER, 0 })
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	m_VAO.Id = VAO;
}

BufferObject::BufferObject(int size, const void* Data)
	:m_VAO({ GL_VERTEX_ARRAY, 0 }),
	 m_VBO({ GL_ARRAY_BUFFER, 0 }),
	 m_EBO({ GL_ELEMENT_ARRAY_BUFFER, 0 })
{
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, Data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_VBO.Id = VBO;
	m_VBO.Size = size;
	m_VAO.Id = VAO;
}

BufferObject::BufferObject(BufferLayout VBO, BufferLayout VAO, BufferLayout EBO)
	:m_VAO(VAO), m_VBO(VBO), m_EBO(EBO)
{
}

BufferObject::~BufferObject()
{
	switch (m_VBO.Target)
	{
	case GL_VERTEX_ARRAY: glDeleteVertexArrays(1, &m_VBO.Id);
		break;
	case GL_ELEMENT_ARRAY_BUFFER: glDeleteBuffers(1, &m_VBO.Id);
		break;
	case GL_ARRAY_BUFFER: glDeleteBuffers(1, &m_VBO.Id);
	}
	
	switch (m_EBO.Target)
	{
	case GL_VERTEX_ARRAY: glDeleteVertexArrays(1, &m_EBO.Id);
		break;
	case GL_ELEMENT_ARRAY_BUFFER: glDeleteBuffers(1, &m_EBO.Id);
		break;
	case GL_ARRAY_BUFFER: glDeleteBuffers(1, &m_EBO.Id);
	}
	
	switch (m_VAO.Target)
	{
	case GL_VERTEX_ARRAY: glDeleteVertexArrays(1, &m_VAO.Id);
		break;
	case GL_ELEMENT_ARRAY_BUFFER: glDeleteBuffers(1, &m_VAO.Id);
		break;
	case GL_ARRAY_BUFFER: glDeleteBuffers(1, &m_VAO.Id);
	}
}

BufferObject BufferObject::operator=(BufferObject buffer)
{
	CopyBufferFrom(m_VBO, 0, 0, m_VBO.Size);
	CopyBufferFrom(m_EBO, 0, 0, m_EBO.Size);
	return {buffer.m_VBO, buffer.m_VAO, buffer.m_EBO};
}

BufferLayout& BufferObject::CreateVertexBuffer(int size,const void* Data)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, Data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	BufferLayout layout = { GL_ARRAY_BUFFER , VBO, size };
	m_VBO.Id = VBO;
	m_VBO.Size = size;
	return layout;
}

BufferLayout& BufferObject::CreateElementBuffer(int size, const void* Data)
{
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, Data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	BufferLayout layout = { GL_ELEMENT_ARRAY_BUFFER , EBO, size };
	m_EBO.Id = EBO;
	m_EBO.Size = size;
	return layout;
}

BufferLayout& BufferObject::CreateVertexArrayBuffer()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	BufferLayout layout = { GL_VERTEX_ARRAY , VAO };
	m_VAO.Id = VAO;
	return layout;
}

void BufferObject::GenSubData(const void* data, int offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO.Id);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(data), &data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferObject::CopyBufferFrom(BufferLayout buffer, int readoffset, int writeoffset, int size)
{
	glBindBuffer(GL_COPY_READ_BUFFER, buffer.Id);
	switch (buffer.Target)
	{
	case GL_ARRAY_BUFFER : glBindBuffer(GL_COPY_WRITE_BUFFER, this->m_VBO.Id);
		break;
	case GL_VERTEX_ARRAY : glBindBuffer(GL_COPY_WRITE_BUFFER, this->m_VAO.Id);
		break;
	case GL_ELEMENT_ARRAY_BUFFER : glBindBuffer(GL_COPY_WRITE_BUFFER, this->m_EBO.Id);
	}
	
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, readoffset, writeoffset, size);
	UnBind();
}

void BufferObject::BindBuffer(BufferLayout& layout)
{
	switch (layout.Target)
	{
	case GL_VERTEX_ARRAY: glBindVertexArray(layout.Id);
		break;
	default:
		glBindBuffer(layout.Target, layout.Id);
	}
}

void BufferObject::BindBuffer()
{
	BindBuffer(m_VAO);
	BindBuffer(m_VBO);
	BindBuffer(m_EBO);
}

void BufferObject::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	BindBuffer();
	glEnableVertexAttribArray(LayoutPos);
	glVertexAttribPointer(LayoutPos, Size, type, GL_FALSE, Stride * sizeof(float), (void*)(Offset*sizeof(float)));
	UnBind();
}

void BufferObject::EnableVertexAtrrib(int LayoutPos)
{
	glEnableVertexAttribArray(LayoutPos);
}

void BufferObject::DisableVertexAttrib(int LayoutPos)
{
	glDisableVertexAttribArray(LayoutPos);
}

FrameBuffer::FrameBuffer()
	:FrameId(0), RenderId(0), TextureId(0)
{
	glGenFramebuffers(1, &FrameId);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameId);
	
	glGenTextures(1, &TextureId);
	glBindTexture(GL_TEXTURE_2D, TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TextureId, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenRenderbuffers(1, &RenderId);
	glBindRenderbuffer(GL_RENDERBUFFER, RenderId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1240, 640);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RenderId);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FrameId);
}

void FrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::DrawQuad(Shader shader, BufferObject& buffer)
{
	glDisable(GL_DEPTH_TEST);
	shader.On();
	buffer.BindBuffer();
	glBindTexture(GL_TEXTURE_2D, TextureId);
	shader.SetUniformInt("texture1", 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	shader.Off();
	buffer.UnBind();
}


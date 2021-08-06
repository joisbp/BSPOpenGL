#include "VertexBuffer.h"
#include "Graphics.h"

VertexBuffer::VertexBuffer(size_t size, const void* data)
	: m_BufferID(0)
{
	glGenBuffers(1, &m_BufferID);
	Bind();

	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	UnBind();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void VertexBuffer::Bind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#pragma once

class VertexBuffer
{
private:
	unsigned int m_BufferID;

public:

	VertexBuffer(size_t size, const void* data);
	~VertexBuffer();


	void Bind() const;
	void UnBind() const;
};


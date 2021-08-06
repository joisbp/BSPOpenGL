#pragma once
class IndexBuffer
{
private:
	unsigned int m_BufferID;

public:

	IndexBuffer(size_t size, const void* data);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;
};


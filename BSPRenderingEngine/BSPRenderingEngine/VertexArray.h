#pragma once

class VertexLayout;
class VertexBuffer;

class VertexArray
{
private:
	unsigned int m_VertexArrayID;

public:
	VertexArray();
	~VertexArray();

	void AddLayout(VertexLayout& layout, VertexBuffer& buffer);
	void Bind() const;
	void UnBind() const;
};


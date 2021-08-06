#include "VertexArray.h"
#include "Graphics.h"
#include "VertexLayout.h"
#include "VertexBuffer.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VertexArrayID);
}

void VertexArray::AddLayout(VertexLayout& layout, VertexBuffer& buffer)
{
	const auto attribs = layout.GetAttributes();

	Bind();
	buffer.Bind();

	unsigned int offset = 0;

	for (int i = 0; i < attribs.size(); ++i)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attribs[i].Count, attribs[i].Type, GL_FALSE, layout.GetStride(), (void*)offset);

		offset += attribs[i].Count * VertexAttributes::GetSize(attribs[i].Type);
	}

	buffer.UnBind();
	UnBind();
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_VertexArrayID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

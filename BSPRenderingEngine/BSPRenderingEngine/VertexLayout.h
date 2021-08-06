#pragma once
#include "Graphics.h"
#include <vector>

struct VertexAttributes
{
	unsigned int Count;
	unsigned int Type;

	static unsigned int GetSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		}
	}
};

class VertexLayout
{
private:
	std::vector<VertexAttributes> m_Attributes;

	unsigned int m_Stride;

public:
	template<typename T>
	void PushAttribute(unsigned int count);

	template<>
	void PushAttribute<float>(unsigned int count)
	{
		m_Attributes.push_back({count, GL_FLOAT});
		m_Stride += count * VertexAttributes::GetSize(GL_FLOAT);
	}

	inline const std::vector<VertexAttributes>& GetAttributes() const { return m_Attributes; };
	inline unsigned int GetStride() const { return m_Stride; };
};


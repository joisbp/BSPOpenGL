#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};

class Mesh
{
private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	VertexBuffer* m_VB;
	IndexBuffer* m_IB;
	VertexArray* m_VA;
	VertexLayout* m_VL;

public:

	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

	void PushVertex(Vertex vertex);
	void PushIndex(unsigned int index);

	void Draw();
};


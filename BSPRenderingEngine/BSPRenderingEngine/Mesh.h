#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"
#include "Shader.h"
#include "Material.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};

class Mesh
{
private:

	unsigned int m_IndicesCount;

	VertexBuffer* m_VB;
	IndexBuffer* m_IB;
	VertexArray* m_VA;
	VertexLayout* m_VL;
	Material* m_Material;

public:

	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Material* material);

	void PushVertex(Vertex vertex);
	void PushIndex(unsigned int index);

	void Draw(Shader& shader);
};


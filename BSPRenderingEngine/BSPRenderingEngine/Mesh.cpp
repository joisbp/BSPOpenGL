#include "Mesh.h"
#include "Graphics.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	m_Vertices = vertices;
	m_Indices = indices;

	m_VB = new VertexBuffer(sizeof(m_Vertices), &m_Vertices);
	m_IB = new IndexBuffer(sizeof(m_Indices), &m_Indices);

	m_VA = new VertexArray();

	m_VL = new VertexLayout();
	m_VL->PushAttribute<float>(3);
	m_VL->PushAttribute<float>(3);
	m_VL->PushAttribute<float>(2);

	m_VA->AddLayout(*m_VL, *m_VB);
}

void Mesh::Draw()
{
	m_VA->Bind();
	m_IB->Bind();

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);

	m_IB->UnBind();
	m_VA->UnBind();
}

#include "Mesh.h"
#include "Graphics.h"


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Material* material)
	: m_Material(material)
{
	m_IndicesCount = indices.size();

	m_VB = new VertexBuffer(sizeof(Vertex) * vertices.size() , &vertices[0]);
	m_IB = new IndexBuffer(sizeof(unsigned int) * indices.size() , &indices[0]);

	m_VA = new VertexArray();

	m_VL = new VertexLayout();
	m_VL->PushAttribute<float>(3);
	m_VL->PushAttribute<float>(3);
	m_VL->PushAttribute<float>(2);

	m_VA->AddLayout(*m_VL, *m_VB);
}

void Mesh::Draw(Shader& shader)
{
	m_Material->PreDraw(shader);
	m_VA->Bind();
	m_IB->Bind();

	glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, nullptr);

	m_IB->UnBind();
	m_VA->UnBind();
}

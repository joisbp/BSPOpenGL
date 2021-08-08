#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

Model::Model()
{
}

void Model::LoadMesh(aiMesh* mesh)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex v;
		v.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		v.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		v.TexCoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		vertices.push_back(v);
	}

	for (int i = 0; i < mesh->mNumFaces; ++i)
	{
		for(int j =0; j < mesh->mFaces[i].mNumIndices; ++j)
			indices.push_back(mesh->mFaces[i].mIndices[j]);
	}

	Mesh* newMesh = new Mesh(vertices, indices);
	m_Meshes.push_back(newMesh);
}

void Model::Draw()
{
	for (auto itr : m_Meshes)
	{
		itr->Draw();
	}
}

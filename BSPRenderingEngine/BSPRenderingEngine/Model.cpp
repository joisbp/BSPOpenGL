#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Material.h"
#include "Scene.h"
#include <iostream>

Model::Model()
{
}

void Model::LoadMesh(const aiScene* aiscene, aiMesh* mesh, Scene* scene)
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


	Material* material = CreateMaterial(aiscene, mesh, scene);

	Mesh* newMesh = new Mesh(vertices, indices, material);
	m_Meshes.push_back(newMesh);


}

Material* Model::CreateMaterial(const aiScene* aiscene, aiMesh* mesh, Scene* scene)
{
	auto aimaterial = aiscene->mMaterials[mesh->mMaterialIndex];

	Material* mat = new Material();
	
	LoadTextures(aiTextureType::aiTextureType_DIFFUSE, TextureType::Diffuse, scene, mat, aimaterial, scene->GetSceneDirectory());
	LoadTextures(aiTextureType::aiTextureType_SPECULAR, TextureType::Specular, scene, mat, aimaterial, scene->GetSceneDirectory());

	return mat;
}

void Model::LoadTextures(aiTextureType aiTexType, TextureType textureType, Scene* scene, Material* mat,
	aiMaterial* aimaterial, const std::string& directoryPath)
{
	for (int i = 0; i < aimaterial->GetTextureCount(aiTexType); ++i)
	{
		aiString path;
		aimaterial->GetTexture(aiTexType, i, &path);

		std::string texturePath = directoryPath + std::string(path.C_Str());

		auto loadedTex = scene->IsTextureLoaded(texturePath);
		if (loadedTex == nullptr)
		{
			loadedTex = new Texture2D(texturePath, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
			scene->PushLoadedTexture(texturePath, loadedTex);
		}

		mat->PushTexture({ textureType, loadedTex });
	}
}

void Model::Draw(Shader& shader)
{
	for (auto itr : m_Meshes)
	{
		itr->Draw(shader);
	}
}

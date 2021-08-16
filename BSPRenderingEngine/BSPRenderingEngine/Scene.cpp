#include "Scene.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <iostream>

Scene::Scene()
	: m_SceneModel(nullptr)
{}

void Scene::LoadSceneFromFile(const std::string & filePath)
{
	Assimp::Importer importer;

	auto scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

	m_SceneDirectory = filePath.substr(0, filePath.find_last_of('/')) + "/";

	m_SceneModel = new Model();

	LoadModels(scene, scene->mRootNode);

	for (int i = 0; i < scene->mNumMaterials; ++i)
	{
		std::cout << scene->mMaterials[i]->GetName().C_Str() << std::endl;
		std::cout << scene->mMaterials[i]->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE) << std::endl;
		std::cout << scene->mMaterials[i]->GetTextureCount(aiTextureType::aiTextureType_SPECULAR) << std::endl;
		std::cout << scene->mMaterials[i]->GetTextureCount(aiTextureType::aiTextureType_SHININESS) << std::endl;
		std::cout << scene->mMaterials[i]->GetTextureCount(aiTextureType::aiTextureType_AMBIENT_OCCLUSION) << std::endl;
		std::cout << scene->mMaterials[i]->GetTextureCount(aiTextureType::aiTextureType_NORMALS) << std::endl;
	}

}

void Scene::Draw(Shader& shader)
{
	m_SceneModel->Draw(shader);
}

void Scene::LoadModels(const aiScene* scene, const aiNode* node)
{
	// Do something with the node and then Load Modles from the children nodes
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		//
		m_SceneModel->LoadMesh(scene, scene->mMeshes[*node->mMeshes], this);
	}

	//

	for (int i = 0; i < node->mNumChildren; ++i)
	{
		LoadModels(scene, node->mChildren[i]);
	}
}

Texture2D* Scene::IsTextureLoaded(const std::string& pathToTexture)
{
	auto itr = m_SceneTextures.find(pathToTexture);

	if (itr != m_SceneTextures.end())
	{
		return (*itr).second;
	}

	return nullptr;
}

void Scene::PushLoadedTexture(std::string pathToTexture, Texture2D* texture)
{
	m_SceneTextures.insert({pathToTexture, texture});
}

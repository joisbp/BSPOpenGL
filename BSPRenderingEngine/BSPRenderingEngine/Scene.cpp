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

	m_SceneModel = new Model();

	LoadModels(scene, scene->mRootNode);

}

void Scene::Draw()
{
	m_SceneModel->Draw();
}

void Scene::LoadModels(const aiScene* scene, const aiNode* node)
{
	// Do something with the node and then Load Modles from the children nodes
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		//
		m_SceneModel->LoadMesh(scene->mMeshes[*node->mMeshes]);
	}

	//

	for (int i = 0; i < node->mNumChildren; ++i)
	{
		LoadModels(scene, node->mChildren[i]);
	}
}

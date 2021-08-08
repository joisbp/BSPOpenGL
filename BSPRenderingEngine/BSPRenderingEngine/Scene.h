#pragma once

#include <string>
#include <assimp/scene.h>
#include "Model.h"

class Scene
{
private:
	Model* m_SceneModel;
public:
	Scene();

	void LoadSceneFromFile(const std::string& filePath);

	void Draw();

	void LoadModels(const aiScene* scene, const aiNode* node);
};


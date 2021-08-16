#pragma once

#include <string>
#include <assimp/scene.h>
#include "Model.h"
#include "Shader.h"
#include <unordered_map>
#include <string>

class Scene
{
private:
	Model* m_SceneModel;

	std::string m_SceneDirectory;

	std::unordered_map<std::string, Texture2D*> m_SceneTextures;
public:
	Scene();

	void LoadSceneFromFile(const std::string& filePath);

	void Draw(Shader& shader);

	void LoadModels(const aiScene* scene, const aiNode* node);

	inline std::string GetSceneDirectory() { return m_SceneDirectory; }

	Texture2D* IsTextureLoaded(const std::string& pathToTexture);

	void PushLoadedTexture(std::string pathToTexture, Texture2D* texture);
};


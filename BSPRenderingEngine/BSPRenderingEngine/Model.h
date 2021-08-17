#pragma once

#include <assimp/scene.h>
#include "Mesh.h"
#include "Shader.h"
#include <vector>

class Material;
class Scene;

class Model
{
private:
	std::vector<Mesh*> m_Meshes;

public:
	Model();

	void LoadMesh(const aiScene* aiscene, aiMesh* mesh, Scene* scene);

	Material* CreateMaterial(const aiScene* aiscene, aiMesh* mesh, Scene* scene);

	void LoadTextures(aiTextureType aiTexType, TextureType texType, Scene* scene, Material* mat,
		aiMaterial* aimaterial, const std::string& texturePath);

	void Draw(Shader& shader);

	inline int GetNumMeshes() { return m_Meshes.size(); }
};


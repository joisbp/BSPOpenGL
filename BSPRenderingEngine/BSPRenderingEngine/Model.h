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

	void Draw(Shader& shader);

	inline int GetNumMeshes() { return m_Meshes.size(); }
};


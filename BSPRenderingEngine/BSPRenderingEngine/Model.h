#pragma once

#include <assimp/scene.h>
#include "Mesh.h"

#include <vector>

class Model
{
private:
	std::vector<Mesh*> m_Meshes;

public:
	Model();

	void LoadMesh(aiMesh* mesh);

	void Draw();

	inline int GetNumMeshes() { return m_Meshes.size(); }
};


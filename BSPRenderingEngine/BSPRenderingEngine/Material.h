#pragma once
#include "Texture2D.h"
#include "Shader.h"
#include <vector>

enum TextureType
{
	Diffuse = 0, 
	Specular,
	Normal
};

struct TextureResource
{
	TextureType type;
	Texture2D* texture;
};

class Material
{
private:
	std::vector<TextureResource> m_Textures;
	
	unsigned int m_DiffuseCount;
	unsigned int m_SpecularCount;
public:
	Material();
	~Material();
	void PreDraw(Shader& shader);

	void PushTexture(TextureResource tex);
};


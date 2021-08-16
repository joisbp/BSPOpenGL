#include "Material.h"

Material::Material()
	: m_DiffuseCount(0), m_SpecularCount(0)
{}

Material::~Material()
{}

void Material::PreDraw(Shader& shader)
{
	for (auto itr : m_Textures)
	{
		switch (itr.type)
		{
		case TextureType::Diffuse:
			itr.texture->Bind(shader.GetLocation("diffuse" + std::to_string(m_DiffuseCount)));
			break;
		case TextureType::Specular:
			itr.texture->Bind(shader.GetLocation("specular" + std::to_string(m_SpecularCount)));
			break;

		default:
			break;
		}
	}
}

void Material::PushTexture(TextureResource tex)
{
	m_Textures.push_back(tex);
}

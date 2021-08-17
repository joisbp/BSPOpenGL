#include "Material.h"

Material::Material()
	: m_DiffuseCount(0), m_SpecularCount(0)
{}

Material::~Material()
{}

void Material::PreDraw(Shader& shader)
{
	std::string name;
	unsigned int location = (unsigned int)-1;
	m_DiffuseCount = 0;
	m_SpecularCount = 0;

	for (auto itr : m_Textures)
	{
		switch (itr.type)
		{
		case TextureType::Diffuse:
			name = "diffuse" + std::to_string(m_DiffuseCount++);
			location = shader.GetLocation(name);

			break;
		case TextureType::Specular:
			name = "specular" + std::to_string(m_SpecularCount++);
			location = shader.GetLocation(name);
			break;

		default:
			break;
		}

		itr.texture->Bind(location);
		shader.SetUniform1(name, location);
	}
}

void Material::PushTexture(TextureResource tex)
{
	m_Textures.push_back(tex);
}

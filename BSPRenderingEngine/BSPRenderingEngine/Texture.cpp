#include "Texture.h"
#include "Graphics.h"

Texture::Texture(std::string filePath)
{
	glGenTextures(1, &m_TextureID);

	m_FilePath = filePath;
}

Texture::~Texture()
{}

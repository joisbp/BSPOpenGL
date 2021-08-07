#include "Texture2D.h"
#include "stb_image.h"

Texture2D::Texture2D(std::string filePath, GLint internalFormat, GLenum format, GLenum type)
	:Texture(filePath)
{
	int width, height, numChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &numChannels, 0);

	if (data != nullptr)
	{
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		UnBind();
	}

	stbi_image_free(data);
}

Texture2D::~Texture2D()
{}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture2D::Bind(unsigned int location)
{
	glActiveTexture(GL_TEXTURE0 + location);
	Bind();
}

void Texture2D::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

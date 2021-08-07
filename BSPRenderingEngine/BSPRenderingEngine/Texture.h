#pragma once

#include <string>

class Texture
{
protected:
	unsigned int m_TextureID;

	std::string m_FilePath;

public:
	Texture(std::string filePath);
	~Texture();

	virtual void Bind() = 0;
	virtual void Bind(unsigned int location) = 0;
	virtual void UnBind() = 0;
};


#pragma once
#include "Texture.h"
#include "Graphics.h"

class Texture2D :
    public Texture
{
public:

    Texture2D(std::string filePath, GLint internalFormat, GLenum format, GLenum type);
    ~Texture2D();

    virtual void Bind() override;
    virtual void Bind(unsigned int location) override;
    virtual void UnBind() override;
};


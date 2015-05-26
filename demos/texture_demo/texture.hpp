#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <string>
#include "utils/exceptions.hpp"

class Texture
{
public:
    Texture(GLenum textureTarget, const std::string& fileName);
    virtual ~Texture();
    void bind(GLenum textureUnit);

    int width() { return mWidth; }
    int height() { return mHeight; }

private:
    GLenum mTextureTarget;
    GLuint mTextureObject;
    int mWidth;
    int mHeight;
    unsigned char* mData;
    GLenum mFormat;
    void loadFile(const std::string& fileName);
};

#endif // TEXTURE_HPP

#include "texture.hpp"
#include <stb_image.h>
#include "utils/logger.hpp"
#include "utils/utils.hpp"

using namespace std;

Texture::Texture(GLenum textureTarget, const std::string& fileName)
{
    loadFile(fileName);
    mTextureTarget = textureTarget;
    glGenTextures(1, &mTextureObject);
    glBindTexture(mTextureTarget, mTextureObject);
    glTexImage2D(mTextureTarget, 0, GL_RGBA, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, mData);
    glTexParameterf(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(mTextureTarget, 0);
}

Texture::~Texture()
{
    stbi_image_free(mData);
    glDeleteTextures(1, &mTextureObject);
}

void Texture::bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(mTextureTarget, mTextureObject);
}

void Texture::loadFile(const string& fileName)
{
    int n;
    string s{getBasePath() + fileName};
    mData = stbi_load(s.c_str(), &mWidth, &mHeight, &n, 0);
    if (not mData) {
        throw Exception("Cannot load file: " + s);
    }
    //TODO: stupid recognition of format
    mFormat = n = 3 ? GL_RGB : GL_RGBA;
}

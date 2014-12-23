#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <GL/glew.h>
#include <string>
#include <ostream>
#include <vector>
#include <memory>

class Attribute
{
public:
    Attribute(GLint index, GLint size, GLint type, GLchar* name, GLint fullSize):
        mIndex{index}, mSize{size}, mType{type}, mName{name}, mFullSize(fullSize) {}

    GLint mIndex;
    GLint mSize;
    GLint mType;
    GLint mFullSize;
    std::string mName;

    friend std::ostream& operator<<(std::ostream& of, const Attribute& attr) {
        return of << "Attrib: " << attr.mName << " idx: " << attr.mIndex << std::hex
                  << " type: " << attr.mType << " size: " << attr.mSize << std::dec
                  << " fullSize: " << attr.mFullSize;
    }
};

typedef std::vector<GLbyte> DataVector;
typedef std::shared_ptr<DataVector> DataVectorPtr;
typedef std::vector<Attribute> AttributeVector;
typedef std::shared_ptr<AttributeVector> AttributeVectorPtr;

class Buffer
{
public:
    Buffer(GLbyte* data, size_t size);
    ~Buffer();
    void bind();
    void unBind();
    void setAttributes(AttributeVectorPtr attrs);

private:
    GLuint mVertexBufferId;
    DataVectorPtr mData;
    GLenum mTarget;
};

#endif // BUFFER_HPP

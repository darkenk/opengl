#include "buffer.hpp"
#include "logger.hpp"

using namespace std;

Buffer::Buffer(GLbyte* data, size_t size):
    /*mData{data}*/ mTarget{GL_ARRAY_BUFFER}
{
    glGenBuffers(1, &mVertexBufferId);
    bind();
//    glBufferData(mTarget, mData->size(), mData->data(), GL_STATIC_DRAW);
    LOGV << "size: " << size << "data: " << data;
    glBufferData(mTarget, size, data, GL_STATIC_DRAW);
    unBind();
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &mVertexBufferId);
}

void Buffer::bind()
{
    glBindBuffer(mTarget, mVertexBufferId);
}

void Buffer::unBind()
{
    glBindBuffer(mTarget, 0);
}

void Buffer::setAttributes(AttributeVectorPtr attrs)
{
    bind();
    GLsizei stride{0};
    for(Attribute& attr : *attrs) {
        stride += attr.mFullSize;
    }
    LOGV << " stride " << stride;
    GLsizei offset{0};
    for(Attribute& attr : *attrs) {
        glEnableVertexAttribArray(attr.mIndex);
        glVertexAttribPointer(attr.mIndex, attr.mSize, attr.mType, GL_FALSE,
                              stride, reinterpret_cast<GLvoid*>(offset));
        offset += 16;
    }
    unBind();
}

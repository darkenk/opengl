#ifndef IBUFFER_HPP
#define IBUFFER_HPP

#include <GL/glew.h>
#include <ostream>
#include <vector>
#include <memory>

class Attribute
{
public:
    Attribute(GLuint index, GLchar* name, GLint fullSize, GLuint location):
        mIndex{index}, mFullSize(fullSize), mName{name}, mLocation{location} {}

    GLuint mIndex;
    GLint mFullSize;
    std::string mName;
    GLuint mLocation;

    friend std::ostream& operator<<(std::ostream& of, const Attribute& attr) {
        return of << "Attrib: " << attr.mName << " idx: " << attr.mIndex
                  << " fullSize: " << attr.mFullSize << " location: " << attr.mLocation;
    }
};

typedef std::vector<Attribute> AttributeVector;
typedef std::shared_ptr<AttributeVector> AttributeVectorPtr;

class  IBuffer
{
public:
    virtual ~IBuffer();
    virtual void bind() const = 0;
    virtual void unBind() const = 0;
    virtual void setAttributes(const AttributeVector& attrs) const;
    virtual GLsizei size() const = 0;
};

#endif // IBUFFER_HPP

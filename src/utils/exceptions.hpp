#ifndef GL_EXCEPTIONS_HPP
#define GL_EXCEPTIONS_HPP

#include <stdexcept>

class GLException : public std::logic_error
{
public:
    GLException(const std::string& msg) : std::logic_error(msg) {}
//    virtual ~GLException();
};

#endif // GL_EXCEPTIONS_HPP

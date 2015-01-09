#include "utils.hpp"
#include "logger.hpp"
#include "exceptions.hpp"
#include <GL/glu.h>

using namespace std;

static string gBasePath;

string getBasePath() {
    return gBasePath;
}

void setBasePath(const string &path) {
    gBasePath = path;
}

constexpr GLsizei FLOAT_SIZE = 4;

GLint convertGLTypeToSize(GLenum type)
{
    switch(type) {
    case GL_FLOAT_VEC2: return 2 * FLOAT_SIZE;
    case GL_FLOAT_VEC3: return 3 * FLOAT_SIZE;
    case GL_FLOAT_VEC4: return 4 * FLOAT_SIZE;
    default: return 0;
    }
}

void checkGlError(const char* funcName) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        string msg = funcName;
        msg.append(" ");
        msg.append(reinterpret_cast<const char*>(gluErrorString(error)));
        throw Exception(msg);
    }
}

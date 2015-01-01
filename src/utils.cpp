#include "utils.hpp"
#include "logger.hpp"

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

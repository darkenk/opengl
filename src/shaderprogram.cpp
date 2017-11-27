#include "shaderprogram.hpp"
#include "utils/exceptions.hpp"
using namespace std;

ShaderProgram::~ShaderProgram()
{
    auto iter = mShaderIds.begin();
    for ( ; iter != mShaderIds.end(); iter++) {
        glDetachShader(mProgramId, *iter);
        glDeleteShader(*iter);
    }
    glDeleteProgram(mProgramId);
}

void ShaderProgram::checkCompilationError(GLuint shaderId)
{
    GLint success{0};
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success) {
        return;
    }
    GLint logSize{0};
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);
    GLchar* errorLog = new GLchar[logSize];
    glGetShaderInfoLog(shaderId, logSize, &logSize, errorLog);
    string msg{"Compilation error "};
    msg.append(errorLog);
    delete[] errorLog;
    fprintf(stderr, "%s\n", msg.c_str());
    throw new GLException(msg);
}

void ShaderProgram::initUniforms() {
    GLint uniformsLength;
    glGetProgramiv(mProgramId, GL_ACTIVE_UNIFORMS, &uniformsLength);
    constexpr GLsizei BUFF_SIZE = 256;
    GLchar name[BUFF_SIZE];
    GLsizei length;
    GLint size;
    GLenum type;
    GLint location;
    for (GLuint i = 0; i < static_cast<GLuint>(uniformsLength); i++) {
        glGetActiveUniform(mProgramId, i, BUFF_SIZE, &length, &size, &type, name);
        location = glGetUniformLocation(mProgramId, name);
        mUniforms.insert(make_pair(string{name}, location));
    }
}

void ShaderProgram::activate() {
    glUseProgram(mProgramId);
}

void ShaderProgram::deactivate() {
    glUseProgram(0);
}

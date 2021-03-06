/**
 * Copyright (C) 2014, Dariusz Kluska <darkenk@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the {organization} nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "shader.hpp"
#include <fstream>
#include <iomanip>
#include "utils/exceptions.hpp"
#include "utils/utils.hpp"
#include "utils/logger.hpp"
#include "buffer.hpp"
#include "utils/make_unique.hpp"

using namespace std;

Shader::Shader(const std::vector<std::pair<GLuint, const string>>& shaders) :
    mProgramId(0)
{
    glGetError();
    for (const auto& shader : shaders) {
        mShaderIds.push_back(createShader(shader.second, shader.first));
    }
    createProgram();
    initUniforms();
}

Shader::~Shader()
{
    auto iter = mShaderIds.begin();
    for ( ; iter != mShaderIds.end(); iter++) {
        glDetachShader(mProgramId, *iter);
        glDeleteShader(*iter);
    }
    glDeleteProgram(mProgramId);
}

unique_ptr<string> Shader::loadShader(const string& fileName)
{
    string s{getBasePath() + fileName};
    ifstream file{s, ios_base::in};
    if (not file.good()) {
        throw Exception("No such file: " + s);
    }
    string line;
    unique_ptr<string> shader = make_unique<string>();
    while (getline(file, line)) {
        shader->append(line);
        shader->append(string{'\n'});
    }
    return shader;
}

GLuint Shader::createShader(const string& fileName, GLuint shaderType)
{
    unique_ptr<string> shader = loadShader(fileName);
    GLuint shaderId = glCreateShader(shaderType);
    const char* str = shader->c_str();
    glShaderSource(shaderId, 1, &str, nullptr);
    glCompileShader(shaderId);
    checkCompilationError(shaderId, fileName);
    return shaderId;
}

void Shader::checkCompilationError(GLuint shaderId, const string& fileName)
{
    GLint success{0};
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (not success) {
        GLint logSize{0};
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);
        GLchar* errorLog = new GLchar[logSize];
        glGetShaderInfoLog(shaderId, logSize, &logSize, errorLog);
        string msg{"Compilation error in " + fileName + " " + errorLog};
        delete[] errorLog;
        throw Exception(msg);
    }
}

void Shader::createProgram()
{
    mProgramId = glCreateProgram();
    for (auto shaderId : mShaderIds) {
        glAttachShader(mProgramId, shaderId);
    }
    glLinkProgram(mProgramId);
    checkGlError(__FUNCTION__);
}

AttributeVectorPtr Shader::getAllAttributes()
{
    // TODO: ugly function, needs refactor
    use();
    mAttributes.clear();
    GLint attrLength;
    glGetProgramiv(mProgramId, GL_ACTIVE_ATTRIBUTES, &attrLength);
    constexpr GLsizei BUFF_SIZE = 256;
    GLchar name[BUFF_SIZE]; // name of attribute
    GLsizei length; // length of string written by gl
    GLint size; // size of attribute
    GLenum type; // type of attribute
    GLint location;
    AttributeVectorPtr attrs{new AttributeVector};
    for (GLuint i = 0; i < static_cast<GLuint>(attrLength); i++) {
        glGetActiveAttrib(mProgramId, i, BUFF_SIZE, &length, &size, &type, name);
        location = glGetAttribLocation(mProgramId, name);
        Attribute a{i, name, convertGLTypeToSize(type), static_cast<GLuint>(location)};
        attrs->push_back(a);
        mAttributes.insert(make_pair(string{name}, location));
    }
    unUse();
    return attrs;
}

void Shader::initUniforms()
{
    use();
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
        LOGV << "Uniform " << location << " " << type << " " << name;
        mUniforms.insert(make_pair(string{name}, location));
    }
    unUse();
}

void Shader::use() {
    glUseProgram(mProgramId);
}

void Shader::unUse() {
    glUseProgram(0);
}

GLint Shader::getUniform(const string& name)
{
    try {
        return static_cast<GLint>(mUniforms.at(name));
    } catch (std::out_of_range& ) {
        // TODO: this is just a backward compatibility
        return -1;
    }
}

GLint Shader::getAttribute(const string& name)
{
    return static_cast<GLint>(mAttributes.at(name));
}

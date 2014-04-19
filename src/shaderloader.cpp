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
#include "shaderloader.hpp"
#include <fstream>
#include <iomanip>
#include "exceptions.hpp"

using namespace std;

string ShaderLoader::mLaunchedPath = "";

ShaderLoader::ShaderLoader(const char* fragmentShader, const char* vertexShader) :
    mProgramId(0)
{
    glGetError();
    mShaderIds.push_back(createShader(fragmentShader, GL_FRAGMENT_SHADER));
    mShaderIds.push_back(createShader(vertexShader, GL_VERTEX_SHADER));
    createProgram();
}

ShaderLoader::~ShaderLoader()
{
    vector<GLuint>::iterator iter = mShaderIds.begin();
    for( ; iter != mShaderIds.end(); iter++) {
        glDetachShader(mProgramId, *iter);
        glDeleteShader(*iter);
    }
    glDeleteProgram(mProgramId);
}

GLuint ShaderLoader::programId()
{
    return mProgramId;
}

char* ShaderLoader::loadShader(const char *fileName)
{
    std::string s(mLaunchedPath);
    s.append(fileName);
    std::ifstream file(s);
    if (!file.good()) {
        file.close();
        string msg = "No such file: ";
        msg += fileName;
        throw Exception(msg);
    }
    file.seekg (0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    char* shader = new char[size+1];
    shader[size] = '\0';
    file.read(shader, size);
    file.close();
    return shader;
}

GLuint ShaderLoader::createShader(const char *fileName, GLuint shaderType)
{
    const GLchar* shader = loadShader(fileName);
    GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shader, NULL);
    glCompileShader(shaderId);
    delete[] shader;
    return shaderId;
}

void ShaderLoader::createProgram()
{
    mProgramId = glCreateProgram();
    std::vector<GLuint>::iterator iter = mShaderIds.begin();
    while(iter != mShaderIds.end()) {
        glAttachShader(mProgramId, *iter);
        iter++;
    }
    glLinkProgram(mProgramId);
    GLuint error = glGetError();
    if (error != GL_NO_ERROR) {
        throw Exception(reinterpret_cast <const char*>(gluErrorString(error)));
    }
}

void ShaderLoader::setLaunchedPath(std::string &s)
{
    mLaunchedPath = s;
}
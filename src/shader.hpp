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
#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include <memory>
#include "buffer.hpp"
#include <map>

class Shader
{
public:
    Shader(const std::vector<std::pair<GLuint, const std::string>>& shaders);
    ~Shader();
    void use();
    void unUse();
    GLint getUniform(const std::string& name);
    GLint getAttribute(const std::string& name);
    AttributeVectorPtr getAllAttributes();

private:
    std::unique_ptr<std::string> loadShader(const std::string& fileName);
    GLuint createShader(const std::string& fileName, GLuint shaderType);
    void checkCompilationError(GLuint shaderId, const std::string& fileName);
    void initUniforms();
    void createProgram();
    GLuint mProgramId;
    std::vector<GLuint> mShaderIds;
    std::map<std::string, GLuint> mUniforms;
    std::map<std::string, GLuint> mAttributes;
};

#endif // SHADERLOADER_H

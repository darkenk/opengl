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
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "shader.hpp"

class Light
{
public:
    Light();
    ~Light();

    void addShader(std::shared_ptr<Shader> shader);
    void setAmbientColor(glm::vec4& color);
    glm::vec4 getAmbientColor();
    void setAmbientIntensity(GLfloat intensity);
    GLfloat getAmbientIntensity();

    void setDiffuseDirection(glm::vec4& direction);
    glm::vec4 getDiffuseDirection();
    void setDiffuseIntensity(GLfloat intensity);
    GLfloat getDiffuseIntensity();

private:
    inline void setVector4InShaders(const std::string& variableName, glm::vec4& value);
    inline void setAmbientIntensityInShaders(const std::string& variableName, GLfloat value);

    std::vector<std::shared_ptr<Shader>> mShaders;
    glm::vec4 mAmbientColor;
    GLfloat mAmbientIntensity;
    glm::vec4 mDiffuseDirection;
    GLfloat mDiffuseIntensity;
};

#endif // LIGHT_HPP

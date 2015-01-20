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
#include <glm/gtc/type_ptr.hpp>
#include "light.hpp"

using namespace std;

Light::Light() :
    mAmbientColor{glm::vec4{0.0f, 1.0f, 1.0f, 1.0f}},
    mAmbientIntensity{1.0f},
    mDiffuseDirection{glm::vec4{1.0f, 1.0f, 0.0f, 1.0f}},
    mDiffuseIntensity{1.0f}
{
}

Light::~Light()
{
}

void Light::addShader(shared_ptr<Shader> shader)
{
    mShaders.push_back(shader);
    setAmbientColor(mAmbientColor);
    setAmbientIntensity(mAmbientIntensity);
    setDiffuseDirection(mDiffuseDirection);
    setDiffuseIntensity(mDiffuseIntensity);
}

void Light::setAmbientColor(glm::vec4& color)
{
    mAmbientColor = color;
    setVector4InShaders("gDirectionalLight.Color", mAmbientColor);
}

glm::vec4 Light::getAmbientColor()
{
    return mAmbientColor;
}

void Light::setAmbientIntensity(GLfloat intensity)
{
    mAmbientIntensity = intensity;
    setAmbientIntensityInShaders("gDirectionalLight.AmbientIntensity", intensity);
}

GLfloat Light::getAmbientIntensity()
{
    return mAmbientIntensity;
}

glm::vec4 Light::getDiffuseDirection()
{
    return mDiffuseDirection;
}

void Light::setDiffuseDirection(glm::vec4& direction)
{
    mDiffuseDirection = direction;
    setVector4InShaders("gDirectionalLight.Direction", direction);
}

void Light::setDiffuseIntensity(GLfloat intensity)
{
    mDiffuseIntensity = intensity;
    setAmbientIntensityInShaders("gDirectionalLight.DiffuseIntensity", intensity);
}

GLfloat Light::getDiffuseIntensity()
{
    return mDiffuseIntensity;
}

void Light::setVector4InShaders(const string& variableName, glm::vec4& value)
{
    for (auto shader : mShaders) {
        shader->use();
        glUniform4fv(shader->getUniform(variableName.c_str()), 1, glm::value_ptr(value));
        shader->unUse();
    }
}

void Light::setAmbientIntensityInShaders(const string& variableName, GLfloat value)
{
    for (auto shader : mShaders) {
        shader->use();
        glUniform1f(shader->getUniform(variableName.c_str()), value);
        shader->unUse();
    }
}

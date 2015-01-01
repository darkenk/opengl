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
#include "colouredobject.hpp"
#include "shader.hpp"
#include <GL/glu.h>
#include <iostream>
#include "exceptions.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "logger.hpp"

using namespace std;

ColouredObject::ColouredObject(std::shared_ptr<IObject> object)
{
    mShader = unique_ptr<Shader>(new Shader("./fragment.glsl", "./vertex.glsl"));
    mObject = object;

    glGetError();

    //vao
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    //vertices
    mVertexBuffer = unique_ptr<Buffer<Vertex>>{new Buffer<Vertex>{object->getVertices()}};
    mVertexBuffer->setAttributes(mShader->getAllAttributes());

    //indices;
    mIndexBuffer = unique_ptr<Buffer<unsigned int>>{new Buffer<unsigned int>{object->getIndices(),
                                                    GL_ELEMENT_ARRAY_BUFFER}};

    mShader->use();
    //projection matrix
    mModelId = mShader->getUniform("gWorld");

    //set light
    glm::vec4 lightColor = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    float lightIntense = 0.7f;
    glUniform4fv(mShader->getUniform("gDirectionalLight.Color"), 1, glm::value_ptr(lightColor));
    glUniform1f(mShader->getUniform("gDirectionalLight.AmbientIntensity"), lightIntense);

    checkError(__FUNCTION__);
}

ColouredObject::~ColouredObject()
{
    mShader.release();
    glDeleteVertexArrays(1, &mVao);
}

void ColouredObject::render()
{
    mShader->use();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUniformMatrix4fv(mModelId, 1, GL_FALSE, glm::value_ptr(mMVP));
    glBindVertexArray(mVao);
    glDrawElements(GL_TRIANGLES, mIndexBuffer->size(), GL_UNSIGNED_INT, 0);
    mShader->unUse();
}

void ColouredObject::setVpMatrix(glm::mat4& matrix)
{
    mMVP = matrix * getModel();
}
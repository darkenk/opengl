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
#include "simpleobject.hpp"
#include "shader.hpp"
#include <GL/glu.h>
#include <iostream>
#include "exceptions.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

SimpleObject::SimpleObject(std::shared_ptr<IObject> object)
{
    mShaderLoader = std::unique_ptr<Shader>(new Shader("./fragment.glsl", "./vertex.glsl"));
    mObject = object;

    glGetError();

    //vao
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    //vertices
    glGenBuffers(1, &mVertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, mObject->getVertices()->size() * sizeof(Vertex) , mObject->getVertices()->data(), GL_STATIC_DRAW);
    // enable position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    // enable color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (sizeof(Vertex::position)));

    //indices;
    glGenBuffers(1, &mIndicesBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mObject->getIndices()->size() * sizeof(unsigned int), mObject->getIndices()->data(), GL_STATIC_DRAW);

    //projection matrix
    mModelId = mShaderLoader->getUniform("gWorld");
    mModel = glm::mat4();

    checkError(__FUNCTION__);
}

SimpleObject::~SimpleObject()
{
    glUseProgram(0);
    mShaderLoader.release();
    glDeleteBuffers(1, &mIndicesBufferId);
    glDeleteBuffers(1, &mVertexBufferId);
    glDeleteVertexArrays(1, &mVao);
}

void SimpleObject::render()
{
    mShaderLoader->use();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUniformMatrix4fv(mModelId, 1, GL_FALSE, glm::value_ptr(mMVP));
    glBindVertexArray(mVao);
    glDrawElements(GL_TRIANGLES, mObject->getIndices()->size(), GL_UNSIGNED_INT, 0);
    mShaderLoader->unUse();
}

void SimpleObject::setVpMatrix(glm::mat4& matrix)
{
    mMVP = mModel * matrix;
}

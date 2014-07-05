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
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "terrainobject.hpp"
#include "shaderloader.hpp"
#include "exceptions.hpp"
#include "logger.hpp"

TerrainObject::TerrainObject()
{
    init();
}

TerrainObject::~TerrainObject()
{
    release();
}

bool TerrainObject::init()
{
    try {
        mShaderLoader = std::unique_ptr<ShaderLoader>(new ShaderLoader("./terrain_frag.glsl", "./terrain_vert.glsl"));
    } catch (std::exception& e) {
        LOGE << e.what();
        return false;
    }

    mWidth = 24;
    mHeight = 24;
    mTerrain.generate(mWidth, mHeight);
    GLuint i = 0;
    GLfloat vertices[mWidth * mHeight * 4];
    for (GLuint y = 0; y < mHeight; y++) {
        for (GLuint x = 0; x < mWidth; x++) {
            vertices[i++] = (float) x;
            vertices[i++] = 0.0f;
            vertices[i++] = (float) y;
            vertices[i++] = 1.0f;
        }
    }

    GLenum ErrorCheckValue = glGetError();

    mModelId = glGetUniformLocation(mShaderLoader->programId(), "gWorld");
    mModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    glGenVertexArrays(1, &mVertexArrayId);
    glBindVertexArray(mVertexArrayId);
    glGenBuffers(1, &mVertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint indices[3 * 2 * (mWidth - 1) * (mHeight - 1)];
    i = 0;
    GLuint upperLine;
    GLuint lowerLine;
    for (GLuint y = 1; y < mHeight; y++) {
        upperLine = (y - 1) * mWidth;
        lowerLine = y * mWidth;
        for (GLuint x = 1; x < mWidth; x++) {
            indices[i++] = upperLine + x - 1;
            indices[i++] = upperLine + x;
            indices[i++] = lowerLine + x;

            indices[i++] = upperLine + x - 1;
            indices[i++] = lowerLine + x;
            indices[i++] = lowerLine + x - 1;
        }
    }

    glGenBuffers(1, &mIndicesBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
            GL_STATIC_DRAW);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        LOGE << "ERROR: Could not create a VBO: "
                << gluErrorString(ErrorCheckValue);
        return false;
    }

    return true;
}

void TerrainObject::render()
{
    glUseProgram(mShaderLoader->programId());
    glUniformMatrix4fv(mModelId, 1, GL_FALSE, glm::value_ptr(mMVP));
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBufferId);
    glDrawElements(GL_TRIANGLES, 3 * 2 * (mWidth - 1) * (mHeight - 1),
            GL_UNSIGNED_INT, 0);
}

bool TerrainObject::release()
{
    mShaderLoader.reset();
    GLenum ErrorCheckValue = glGetError();

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &mIndicesBufferId);
    glDeleteBuffers(1, &mVertexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &mVertexArrayId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        LOGE << "ERROR: Could not destroy the VBO: "
                << gluErrorString(ErrorCheckValue);

        return false;
    }

    return true;
}

void TerrainObject::setVpMatrix(glm::mat4& matrix)
{
    mMVP = mModel * matrix;
}

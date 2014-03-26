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
#include "triangleobject.hpp"
#include "shaderloader.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <iostream>

TriangleObject::TriangleObject()
{
}

bool TriangleObject::init()
{
    createShaders();

    GLfloat Vertices[] = {
        -0.8f, -0.8f, 0.0f, 1.0f,
         0.0f,  0.8f, 0.0f, 1.0f,
         0.8f, -0.8f, 0.0f, 1.0f
    };
 
    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };
 
    GLenum ErrorCheckValue = glGetError();
     
    glGenVertexArrays(1, &mVertexArrayId);
    glBindVertexArray(mVertexArrayId);
 
    glGenBuffers(1, &mVertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
     
    glGenBuffers(1, &mColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, mColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
 
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        std::cerr << "ERROR: Could not create a VBO: " <<
            gluErrorString(ErrorCheckValue) << std::endl;
        return false;
    }
    return true;
}

void TriangleObject::render()
{
    glUseProgram(mProgramId);
    glBindVertexArray(mVertexArrayId);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool TriangleObject::release()
{
    releaseShaders();
    GLenum ErrorCheckValue = glGetError();
 
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
     
    glBindBuffer(GL_ARRAY_BUFFER, 0);
 
    glDeleteBuffers(1, &mColorBufferId);
    glDeleteBuffers(1, &mVertexBufferId);
 
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &mVertexArrayId);
 
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        std::cerr << "ERROR: Could not destroy the VBO: " <<
            gluErrorString(ErrorCheckValue) << std::endl;
 
        return false;
    }
    return true;
}

bool TriangleObject::createShaders()
{
    ShaderLoader sl;
    GLenum ErrorCheckValue = glGetError();

    sl.loadShader("./vertex.glsl");
    const char * v =  sl.getShader();
    mVertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(mVertexShaderId, 1, &v, NULL);
    glCompileShader(mVertexShaderId);
    sl.releaseShader();

    if (!sl.loadShader("./fragment.glsl")) {
        std::cerr << "sl.loadShader failed" << std::endl;
    }
    const char * f = sl.getShader();
    mFragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mFragmentShaderId, 1, &f, NULL);
    glCompileShader(mFragmentShaderId);
    sl.releaseShader();
 
    mProgramId = glCreateProgram();
    glAttachShader(mProgramId, mVertexShaderId);
    glAttachShader(mProgramId, mFragmentShaderId);
    glLinkProgram(mProgramId);
 
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        std::cerr << "ERROR: Could not create the shaders: " <<
            gluErrorString(ErrorCheckValue) << std::endl;

        return false;
    }
    return true;
}

bool TriangleObject::releaseShaders()
{
    GLenum ErrorCheckValue = glGetError();
    glUseProgram(0);

    glDetachShader(mProgramId, mVertexShaderId);
    glDetachShader(mProgramId, mFragmentShaderId);
    glDeleteShader(mFragmentShaderId);
    glDeleteShader(mVertexShaderId);
    glDeleteProgram(mProgramId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        std::cerr << "ERROR: Could not destroy the shaders8: " <<
            gluErrorString(ErrorCheckValue);
 
        return false;
    }
    return true;
}

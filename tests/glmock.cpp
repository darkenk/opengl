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
#include "glmock.hpp"
#include <pthread.h>
#include <map>

std::map<pthread_t, GLMock* > gMap;

GLMock::GLMock()
{
    pthread_t id = pthread_self();
    GLMock* glmock = (this);
    gMap.insert(std::pair<pthread_t, GLMock* >(id, glmock));
}

GLMock::~GLMock()
{
    gMap.erase(pthread_self());
}

static GLMock* getGLMock()
{
    pthread_t id = pthread_self();
    return gMap.at(id);
}

GLuint mockCreateProgram()
{
    return getGLMock()->CreateProgram();
}

GLuint mockCreateShader(GLenum type)
{
    return getGLMock()->CreateShader(type);
}

void mockShaderSource(GLuint shader, GLsizei count, const GLchar** strings, const GLint* lengths)
{
    getGLMock()->ShaderSource(shader, count, strings, lengths);
}

void mockCompileShader(GLuint shader)
{
    getGLMock()->CompileShader(shader);
}

void mockAttachShader(GLuint program, GLuint shader)
{
    getGLMock()->AttachShader(program, shader);
}

void mockLinkProgram(GLuint program)
{
    getGLMock()->LinkProgram(program);
}

void mockDetachShader(GLuint program, GLuint shader)
{
    getGLMock()->DetachShader(program, shader);
}

void mockDeleteShader(GLuint shader)
{
    getGLMock()->DeleteShader(shader);
}

void mockDeleteProgram(GLuint program)
{
    getGLMock()->DeleteProgram(program);
}

GLenum glGetError()
{
    return getGLMock()->GetError();
}

const GLubyte* gluErrorString(GLenum error)
{
    return getGLMock()->ErrorString(error);
}

PFNGLCREATEPROGRAMPROC __glewCreateProgram = mockCreateProgram;
PFNGLCREATESHADERPROC __glewCreateShader = mockCreateShader;
PFNGLSHADERSOURCEPROC __glewShaderSource = mockShaderSource;
PFNGLCOMPILESHADERPROC __glewCompileShader = mockCompileShader;
PFNGLATTACHSHADERPROC __glewAttachShader = mockAttachShader;
PFNGLLINKPROGRAMPROC __glewLinkProgram = mockLinkProgram;
PFNGLDETACHSHADERPROC __glewDetachShader = mockDetachShader;
PFNGLDELETESHADERPROC __glewDeleteShader = mockDeleteShader;
PFNGLDELETEPROGRAMPROC __glewDeleteProgram = mockDeleteProgram;
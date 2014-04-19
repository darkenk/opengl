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
#ifndef GLMOCK_H_
#define GLMOCK_H_

#include <gmock/gmock.h>
#include <memory>

#if defined(_WIN32) || defined(__WIN32__)
   #define WIN32_LEAN_AND_MEAN
   #include <windows.h>
   #include <GL/glew.h>
   #include <GL/wglew.h>
   #include <GL/glu.h>
#elif defined(linux) || defined(__linux) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
   #include <GL/glew.h>
   #include <GL/glxew.h>
   #include <GL/glu.h>
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
   #include <OpenGL/glew.h>
   #include <OpenGL/glxew.h>
   #include <OpenGL/glu.h>
#else
    #error "WTF?, unsupported platform"
#endif

class GLMock {
public:
    GLMock();
    ~GLMock();
    MOCK_METHOD1( CompileShader, void  (GLuint shader) );
    MOCK_METHOD0( CreateProgram, GLuint  (void) );
    MOCK_METHOD1( CreateShader, GLuint  (GLenum type) );
    MOCK_METHOD1( DeleteProgram, void  (GLuint program) );
    MOCK_METHOD1( DeleteShader, void  (GLuint shader) );
    MOCK_METHOD2( DetachShader, void  (GLuint program, GLuint shader) );
    MOCK_METHOD2( AttachShader, void  (GLuint program, GLuint shader) );
    MOCK_METHOD1( LinkProgram, void  (GLuint program) );
    MOCK_METHOD4( ShaderSource, void  (GLuint shader, GLsizei count, const GLchar** strings, const GLint* lengths) );
    MOCK_METHOD0( GetError, GLenum   (void) );
    MOCK_METHOD1( ErrorString, GLubyte* (GLenum error) );
};

#endif /* GLMOCK_H_ */
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
 * OR TORT (INCLUDING NEgGLMockIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "../src/shaderloader.hpp"
#include "glmock.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdio>
#include <fstream>

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;

const char* TEST_VERTEX_FILE = "/tmp/test_file_vertex_shader";
const char* TEST_VERTEX_SHADER =
        "#version 330\n\n"
        "in vec4 ex_Color;\n"
        "out vec4 out_Color;\n\n"
        "void main(void)\n"
        "{\n"
        "    out_Color = ex_Color;\n"
        "};";

const char* TEST_FRAGMENT_FILE = "/tmp/test_file_fragment_shaders";
const char* TEST_FRAGMENT_SHADER =
        "layout(location=0) in vec4 in_Position;\n"
        "layout(location=1) in vec4 in_Color;\n"
        "out vec4 ex_Color;\n\n"
        "void main(void)\n"
        "{\n"
        "   gGLMock_Position = in_Position;\n"
        "   ex_Color = in_Color;\n"
        "}";

static void createTestShader()
{
    remove(TEST_VERTEX_FILE);
    {
        std::ofstream test(TEST_VERTEX_FILE);
        test << TEST_VERTEX_SHADER;
        test.flush();
    }
    remove(TEST_FRAGMENT_FILE);
    {
        std::ofstream test(TEST_FRAGMENT_FILE);
        test << TEST_FRAGMENT_FILE;
        test.flush();
    }
}

static void removeTestShaders()
{
    remove(TEST_VERTEX_FILE);
    remove(TEST_FRAGMENT_FILE);
}

TEST(ShaderLoaderTest, throw_exception_when_there_is_no_files)
{
    NiceMock<GlMock> gGLMock;
    removeTestShaders();
    EXPECT_ANY_THROW(ShaderLoader(TEST_VERTEX_FILE, TEST_FRAGMENT_FILE));
}

TEST(ShaderLoaderTest, load_shader_from_file)
{
    createTestShader();
    const GLuint vertexShaderId = 1;
    const GLuint fragmentShaderId = 2;
    const GLuint programId = 3;
    NiceMock<GlMock> gGLMock;
    EXPECT_CALL(gGLMock, gl_CreateShader(GL_VERTEX_SHADER)).WillOnce(Return(vertexShaderId));
    EXPECT_CALL(gGLMock, gl_CreateShader(GL_FRAGMENT_SHADER)).WillOnce(Return(fragmentShaderId));
    EXPECT_CALL(gGLMock, gl_ShaderSource(vertexShaderId, _, _, _));
    EXPECT_CALL(gGLMock, gl_ShaderSource(fragmentShaderId, _, _, _));
    EXPECT_CALL(gGLMock, gl_CompileShader(vertexShaderId));
    EXPECT_CALL(gGLMock, gl_CompileShader(fragmentShaderId));
    EXPECT_CALL(gGLMock, gl_CreateProgram()).WillOnce(Return(programId));
    EXPECT_CALL(gGLMock, gl_AttachShader(programId, vertexShaderId));
    EXPECT_CALL(gGLMock, gl_AttachShader(programId, fragmentShaderId));
    EXPECT_CALL(gGLMock, gl_LinkProgram(programId));
    EXPECT_CALL(gGLMock, gl_GetError()).WillRepeatedly(Return(GL_NO_ERROR));
    std::shared_ptr<ShaderLoader> sl = std::shared_ptr<ShaderLoader>(new ShaderLoader(TEST_VERTEX_FILE, TEST_FRAGMENT_FILE));
    EXPECT_EQ(programId, sl->programId());
    sl.reset();
    removeTestShaders();
}

TEST(ShaderLoaderTest, release_shader)
{
    createTestShader();
    NiceMock<GlMock> gGLMock;
    const GLuint vertexShaderId = 1;
    const GLuint fragmentShaderId = 2;
    const GLuint programId = 3;
    EXPECT_CALL(gGLMock, gl_CreateShader(GL_VERTEX_SHADER)).WillOnce(Return(vertexShaderId));
    EXPECT_CALL(gGLMock, gl_CreateShader(GL_FRAGMENT_SHADER)).WillOnce(Return(fragmentShaderId));
    EXPECT_CALL(gGLMock, gl_CreateProgram()).WillOnce(Return(programId));
    ShaderLoader* sl = new ShaderLoader(TEST_VERTEX_FILE, TEST_FRAGMENT_FILE);
    EXPECT_CALL(gGLMock, gl_DetachShader(programId, vertexShaderId));
    EXPECT_CALL(gGLMock, gl_DetachShader(programId, fragmentShaderId));
    EXPECT_CALL(gGLMock, gl_DeleteShader(vertexShaderId));
    EXPECT_CALL(gGLMock, gl_DeleteShader(fragmentShaderId));
    EXPECT_CALL(gGLMock, gl_DeleteProgram(programId));
    delete sl;
    removeTestShaders();
}

TEST(ShaderLoaderTest, exception_when_opengl_error)
{
    createTestShader();
    NiceMock<GlMock> gGLMock;
    EXPECT_CALL(gGLMock, gl_GetError()).WillRepeatedly(Return(-11));
    EXPECT_ANY_THROW(ShaderLoader(TEST_VERTEX_FILE, TEST_FRAGMENT_FILE));
    removeTestShaders();
}

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
#include <gtest/gtest.h>
#include "mockshaderloader.hpp"
#include "../src/simpleobject.hpp"
#include <gmock/gmock.h>
#include "glmock.hpp"
#include <pthread.h>
#include <map>

using testing::_;
using testing::Return;
using testing::InSequence;
using testing::NiceMock;
using testing::ElementsAreArray;
using testing::Args;
using testing::Ne;
using testing::Matcher;
using testing::AtLeast;
using testing::AnyNumber;
using testing::MatcherCast;
using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;
using namespace std;

ACTION(MyThrowException)
{
    throw std::exception();
}

class TriangleObject : public IObject {
public:
    VertexVectorPtr getVertices() {
        VertexVectorPtr v = VertexVectorPtr(new vector<Vertex> ({
            glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
            glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f),
            glm::vec4( 0.0f,  0.5f, 0.0f, 1.0f),
        }));
        return v;
    }
    IndexVectorPtr getIndices() {
        IndexVectorPtr v = IndexVectorPtr(new vector<unsigned int>({0, 1, 2 }));
        return v;
    }
};

class SimpleObjectTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        to = shared_ptr<TriangleObject>(new TriangleObject);
    }

    NiceMock<GlMock> gl;
    NiceMock<MockShaderLoader> sl;
    shared_ptr<TriangleObject> to;
};

TEST_F(SimpleObjectTest, load_shader_in_constructor)
{
    EXPECT_CALL(sl, ctor(_,_));
    SimpleObject so(to);
}

TEST_F(SimpleObjectTest, throw_exception_when_there_is_no_shaders)
{
    EXPECT_CALL(sl, ctor(_,_)).WillOnce(MyThrowException());
    EXPECT_ANY_THROW(SimpleObject so(to));
}

TEST_F(SimpleObjectTest, erase_opengl_buffers_before_buffer_generating)
{
    EXPECT_CALL(gl, gl_GetError()).Times(AnyNumber());
    {
        InSequence s;
        EXPECT_CALL(gl, gl_GetError()).Times(AtLeast(1));
        EXPECT_CALL(gl, gl_GenBuffers(_,_)).Times(AtLeast(1));
    }
    SimpleObject so(to);
}

MATCHER_P2(VerifyArrayFloat, data, count, "Arrays not equal") {
    float* actual = (float*)(arg);
    for (int i = 0; i < count; i++) {
        if (*(data + i) != *(actual + i)) {
            return false;
        }
    }
    return true;
}

MATCHER_P2(VerifyArrayInt, data, count, "Arrays not equal") {
    int* actual = (int*)(arg);
    for (int i = 0; i < count; i++) {
        if (*(data + i) != *(actual + i)) {
            return false;
        }
    }
    return true;
}

TEST_F(SimpleObjectTest, set_array_buffer_with_vertices)
{

    float data[] = {
                    -0.5f, -0.5f, 0.0f, 1.0f,
                     0.5f, -0.5f, 0.0f, 1.0f,
                     0.0f,  0.5f, 0.0f, 1.0f };
    EXPECT_CALL(gl, gl_BindBuffer(Ne(GL_ARRAY_BUFFER),_))
          .Times(AnyNumber());
    EXPECT_CALL(gl, gl_BufferData(Ne(GL_ARRAY_BUFFER),_,_,_))
          .Times(AnyNumber());
    {
        InSequence s;
        EXPECT_CALL(gl, gl_BindBuffer(GL_ARRAY_BUFFER,_));
        EXPECT_CALL(gl, gl_BufferData(GL_ARRAY_BUFFER,48,
                                      VerifyArrayFloat(data, 12),GL_STATIC_DRAW));
    }
    SimpleObject so(to);
}

TEST_F(SimpleObjectTest, set_array_buffer_with_indices)
{
    int data[] = {0,1,2};
    EXPECT_CALL(gl, gl_BindBuffer(Ne(GL_ELEMENT_ARRAY_BUFFER),_))
          .Times(AnyNumber());
    EXPECT_CALL(gl, gl_BufferData(Ne(GL_ELEMENT_ARRAY_BUFFER),_,_,_))
          .Times(AnyNumber());
    {
        InSequence s;
        EXPECT_CALL(gl, gl_BindBuffer(GL_ELEMENT_ARRAY_BUFFER,_));
        EXPECT_CALL(gl, gl_BufferData(GL_ELEMENT_ARRAY_BUFFER, 12, VerifyArrayInt(data, 3), GL_STATIC_DRAW));
    }
    SimpleObject so(to);
}

TEST_F(SimpleObjectTest, throw_exception_if_error_at_the_end_of_initialization)
{
    GLubyte error[] = "TestError\0";
    EXPECT_CALL(gl, glu_ErrorString(_)).WillRepeatedly(Return(error));
    EXPECT_CALL(gl, gl_GetError()).WillRepeatedly(Return(-12));
    EXPECT_ANY_THROW(SimpleObject so(to));
}

TEST_F(SimpleObjectTest, rendering_triangle)
{
    const int programId = 1;
    EXPECT_CALL(sl, programId()).WillRepeatedly(Return(programId));
    EXPECT_CALL(gl, gl_UseProgram(_));
    EXPECT_CALL(gl, gl_UseProgram(programId));
    EXPECT_CALL(gl, gl_DrawElements(GL_TRIANGLES, 3, _, _));
    SimpleObject so(to);
    so.render();
}

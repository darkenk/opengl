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
#include "../src/shaderloader.hpp"
#include <cstdio>
#include <fstream>

const char* TEST_FILE = "/tmp/test_file_shaders";
const char* TEST_SHADER =
        "#version 330\n\n"
        "in vec4 ex_Color;\n"
        "out vec4 out_Color;\n\n"
        "void main(void)\n"
        "{\n"
        "    out_Color = ex_Color;\n"
        "};";

static void createTestShader()
{
    remove(TEST_FILE);
    std::ofstream test(TEST_FILE);
    test << TEST_SHADER;
    test.flush();
}

TEST(ShaderLoaderTest, return_false_when_there_is_no_file)
{
    remove(TEST_FILE);
    ShaderLoader sl;
    EXPECT_FALSE(sl.loadShader(TEST_FILE));
}

TEST(ShaderLoaderTest, load_shader_from_file)
{
    createTestShader();
    ShaderLoader sl;
    EXPECT_TRUE(sl.loadShader(TEST_FILE));
    EXPECT_STREQ(TEST_SHADER, sl.getShader());
    remove(TEST_FILE);
}

TEST(ShaderLoaderTest, release_shader)
{
    createTestShader();
    ShaderLoader sl;
    EXPECT_TRUE(sl.loadShader(TEST_FILE));
    sl.releaseShader();
    EXPECT_EQ(nullptr, sl.getShader());
    remove(TEST_FILE);
}

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
#include "../src/camera.hpp"
#include <iostream>

using namespace std;

//TODO: write implementation for camera, when gLookAt is in different position
const glm::vec3 gPosition(4.0f,3.0f,3.0f);
const glm::vec3 gLookAt(4.0f,3.0f,2.0f);
const glm::vec3 gUp(0.0f,1.0f,0.0f);

ostream& operator<< (ostream &out, const glm::mat4& matrix)
{
    int i, j;
    const int width = 10;
    for (i = 0; i < 4; i++) {
        out << "[ ";
        for (j = 0; j < 3; j++) {
            out << setw(width) << matrix[i][j] << " ";
        }
        out << setw(width) << matrix[i][j] << " ]" << endl;
    }
    return out;
}

void check(const glm::mat4& mat1, const glm::mat4& mat2)
{
    const int width = 4;
    const int height = 4;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            EXPECT_NEAR(mat1[i][j], mat2[i][j], 0.001f);
        }
    }
}

TEST(CameraTest, rotate_left)
{
    Camera camera(gPosition, gLookAt, gUp);
    camera.rotateLeft(PI / 2);
    const glm::mat4& matrix = camera.getMatrix();
    glm::mat4 result = glm::lookAt(gPosition, gLookAt + glm::vec3(-1,0,1), gUp);
    check(matrix, result);
}

TEST(CameraTest, rotate_right)
{
    Camera camera(gPosition, gLookAt, gUp);
    camera.rotateRight(PI / 2);
    const glm::mat4& matrix = camera.getMatrix();
    glm::mat4 result = glm::lookAt(gPosition, gLookAt + glm::vec3(1,0,1), gUp);
    check(matrix, result);
}

TEST(CameraTest, move_left)
{
    Camera camera(gPosition, gLookAt, gUp);
    camera.left(1.0f);
    const glm::mat4& matrix = camera.getMatrix();
    glm::mat4 result = glm::lookAt(gPosition + glm::vec3(-1,0,0), gLookAt + glm::vec3(-1,0,0), gUp);
    check(matrix, result);
}

TEST(CameraTest, move_right)
{
    Camera camera(gPosition, gLookAt, gUp);
    camera.right(1.0f);
    const glm::mat4& matrix = camera.getMatrix();
    glm::mat4 result = glm::lookAt(gPosition + glm::vec3(1,0,0), gLookAt + glm::vec3(1,0,0), gUp);
    check(matrix, result);
}

TEST(CameraTest, move_forward)
{
    Camera camera(gPosition, gLookAt, gUp);
    camera.forward(1.0f);
    const glm::mat4& matrix = camera.getMatrix();
    glm::mat4 result = glm::lookAt(gPosition + glm::vec3(0,0,-1), gLookAt + glm::vec3(0,0,-1), gUp);
    check(matrix, result);
}

TEST(CameraTest, move_backward)
{
    Camera camera(gPosition, gLookAt, gUp);
    camera.backward(1.0f);
    const glm::mat4& matrix = camera.getMatrix();
    glm::mat4 result = glm::lookAt(gPosition + glm::vec3(0,0,1), gLookAt + glm::vec3(0,0,1), gUp);
    check(matrix, result);
}

TEST(CameraTest, move_forward_and_rotate_right)
{
    Camera camera(gPosition, gLookAt, gUp);
    camera.forward(1.0f);
    camera.rotateRight(PI / 2);
    const glm::mat4& matrix = camera.getMatrix();
    glm::mat4 result = glm::lookAt(gPosition + glm::vec3(0,0,-1), gLookAt + glm::vec3(1,0,0), gUp);
    check(matrix, result);
}

TEST(CameraTest, rotate_right_and_move_forward)
{
    Camera camera(gPosition, gLookAt, gUp);
    camera.rotateRight(PI / 2);
    camera.forward(1.0f);
    const glm::mat4& matrix = camera.getMatrix();
    glm::mat4 result = glm::lookAt(gPosition + glm::vec3(1,0,0), gLookAt + glm::vec3(2,0,1), gUp);
    check(matrix, result);
}

TEST(CameraTest, rotate_left_and_move_forward)
{
    Camera camera(gPosition, gLookAt, gUp);
    camera.rotateLeft(PI / 2);
    camera.forward(1.0f);
    const glm::mat4& matrix = camera.getMatrix();
    glm::mat4 result = glm::lookAt(gPosition + glm::vec3(-1,0,0), gLookAt + glm::vec3(-2,0,1), gUp);
    check(matrix, result);
}

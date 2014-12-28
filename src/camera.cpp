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
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <iostream>
#include <sstream>
#include "camera.hpp"
#include "logger.hpp"

using namespace std;

Camera::Camera(const glm::vec3& position,
        const glm::vec3& direction,
        const glm::vec3& up)
{
    mPosition = position;
    mDirection = direction;
    mUp = up;
    mYaw = 0.0f;
    mPitch = 0.0f;
    mRoll = 0.0f;
    update();
}

Camera::~Camera()
{
}

const glm::mat4& Camera::getMatrix()
{
    return mMatrix;
}

void Camera::left(float speed)
{
    mPosition -= mRight * speed;
    update();
}

void Camera::right(float speed)
{
    mPosition += mRight * speed;
    update();
}

void Camera::forward(float speed)
{
    mPosition += mDirection * speed;
    update();
}

void Camera::backward(float speed)
{
    mPosition -= mDirection * speed ;
    update();
}

void Camera::rotateLeft(float angle)
{
    mYaw += angle;
    update();
}

void Camera::rotateRight(float angle)
{
    mYaw -= angle;
    update();
}

void Camera::rotateUp(float angle)
{
    mPitch += angle;
    update();
}

void Camera::rotateDown(float angle)
{
    mPitch -= angle;
    update();
}

string Camera::dump()
{
    stringstream s;
    s << "pos: " << mPosition << " direction: " << mDirection << " up: " << mUp;
    s << " right: " << mRight;
    return s.str();
}

void Camera::update()
{
    glm::mat4 rot = glm::yawPitchRoll(mYaw, mPitch, mRoll);
    mDirection = glm::vec3(rot * glm::vec4(0, 0, -1, 0));
    mUp = glm::vec3(rot * glm::vec4(0, 1, 0, 0));
    mRight = glm::cross(mDirection, mUp);
    glm::vec3 lookAt = mPosition + mDirection;
    mMatrix = glm::lookAt(mPosition, lookAt, mUp);
}

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
#include "camera.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

Camera::Camera(const glm::vec3& position,
        const glm::vec3& lookAt,
        const glm::vec3& up)
{
    mPosition = position;
    mLookAt = lookAt;
    mUp = up;
    //TODO: this not work
    mInitialDirection = glm::normalize(lookAt - position);
    mRotation = glm::quat_cast(glm::lookAt(mPosition, mLookAt, mUp));
    mDelta = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Camera::~Camera()
{
}

const glm::mat4& Camera::getMatrix()
{
    mLookAt = glm::vec3(glm::toMat4(mRotation) * glm::vec4(mInitialDirection, 1.0f)) + mPosition;
    glm::vec3 vector = mLookAt;
    mMatrix = glm::lookAt(mPosition, mLookAt, mUp);
    return mMatrix;
}

void Camera::left(float speed)
{
    mPosition += glm::vec3(glm::toMat4(mRotation) * glm::vec4(-speed, 0.0f, 0.0f, 1.0f));
}

void Camera::right(float speed)
{
    mPosition += glm::vec3(glm::toMat4(mRotation) * glm::vec4(speed, 0.0f, 0.0f, 1.0f));
}

void Camera::forward(float speed)
{
    mPosition += glm::vec3(glm::toMat4(mRotation) * glm::vec4(0.0f, 0.0f, -speed, 1.0f));
}

void Camera::backward(float speed)
{
    mPosition += glm::vec3(glm::toMat4(mRotation) * glm::vec4(0.0f, 0.0f, speed, 1.0f));
}

void Camera::rotateLeft(float angle)
{
    mRotation = glm::rotate(mRotation, angle, glm::vec3(0, 1, 0));
}

void Camera::rotateRight(float angle)
{
    mRotation = glm::rotate(mRotation, -angle, glm::vec3(0, 1, 0));
}

void Camera::rotateUp(float angle)
{
    mRotation = glm::rotate(mRotation, -angle, glm::vec3(1, 0, 0));
}

void Camera::rotateDown(float angle)
{
    mRotation = glm::rotate(mRotation, angle, glm::vec3(1, 0, 0));
}

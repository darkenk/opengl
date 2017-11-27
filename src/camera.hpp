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
#ifndef CAMERA_H_
#define CAMERA_H_

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "units/units.hpp"

class Camera
{
public:
    Camera(const glm::vec3& position = glm::vec3(0, 0, 0),
        const glm::vec3& direction = glm::vec3(0, 0, -1),
        const glm::vec3& up = glm::vec3(0, 1, 0));
    virtual ~Camera();

    const glm::mat4& getMatrix();
    void left(float speed = 0.2f);
    void right(float speed = 0.2f);
    void forward(float speed = 0.2f);
    void backward(float speed = 0.2f);
    void rotateLeft(float angle = 0.1f);
    void rotateRight(float angle = 0.1f);
    void rotateUp(float angle = 0.1f);
    void rotateDown(float angle = 0.1f);
    std::string dump();

    Vector getPosition();

private:
    void update();
    glm::mat4 mMatrix;
    glm::vec3 mUp;
    glm::vec3 mDirection;
    glm::vec3 mRight;
    glm::vec3 mPosition;
    float mYaw;
    float mPitch;
    float mRoll;
};

#endif /* CAMERA_H_ */

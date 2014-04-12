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
#include "renderer.hpp"
#include "terrainobject.hpp"
#include "triangleobject.hpp"
#include <GL/freeglut.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(shared_ptr<Camera> camera)
{
    sRenderer = this;
    mObject = new TerrainObject();
    mObject->init();
    mCamera = camera;
}

Renderer::~Renderer()
{
    sRenderer = nullptr;
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLenum ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        std::cerr << "ERROR: Clear: " <<
            gluErrorString(ErrorCheckValue);
    }
    glm::mat4 tmp = mProjection * mCamera->getMatrix();
    mObject->setVpMatrix(tmp);
    mObject->render();
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        std::cerr << "ERROR: Render: " <<
            gluErrorString(ErrorCheckValue);
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

void Renderer::resize(int width, int height)
{
    mProjection = glm::perspective(45.0f, float(width) / float(height), 0.1f, 100.0f);
    glViewport(0, 0, width, height);
}

void Renderer::cleanup()
{
    mObject->release();
    delete mObject;
    mObject = 0;
}

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
#include <GL/glew.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "renderer.hpp"
#include "terrain.hpp"
#include "colouredobject.hpp"
#include "cube.hpp"
#include "logger.hpp"

using namespace std;

Renderer::Renderer()
{
    glewExperimental = GL_TRUE;
    glewInit();
    mShader = make_shared<Shader>("./fragment.glsl", "./vertex.glsl");
    mLight = make_shared<Light>();
    mLight->addShader(mShader);
    addObject(make_shared<ColouredObject>(make_shared<Cube>(), mShader));
    mCamera = make_shared<Camera>();
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    auto object = make_shared<ColouredObject>(make_shared<Terrain>(1024, 1024), mShader);
    glm::mat4 m = glm::translate(glm::mat4(), glm::vec3(-12.0f, -3.0f, -24.0f));
    object->setModel(m);
    addObject(object);
}

Renderer::~Renderer()
{
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 tmp = mProjection * mCamera->getMatrix();
    for (auto object : mObjects) {
        object->setVpMatrix(tmp);
        object->render();
    }
    checkGlError(__FUNCTION__);
}

void Renderer::resize(int width, int height)
{
    mProjection = glm::perspective(45.0f, float(width) / float(height), 0.1f, 100.0f);
    glViewport(0, 0, width, height);
}

void Renderer::addObject(shared_ptr<IRenderableObject> object)
{
    mObjects.push_back(object);
}

void Renderer::handleKey(int key)
{
    // TODO is it possible to make it more beautiful?
    switch (static_cast<unsigned char>(key)) {
    case 'w':
        mCamera->forward();
        break;
    case 's':
        mCamera->backward();
        break;
    case 'a':
        mCamera->left();
        break;
    case 'd':
        mCamera->right();
        break;
    case 'q':
        mCamera->rotateLeft();
        break;
    case 'e':
        mCamera->rotateRight();
        break;
    case 'r':
        mCamera->rotateUp();
        break;
    case 'f':
        mCamera->rotateDown();
        break;
    }
}

shared_ptr<Light> Renderer::getLight()
{
    return mLight;
}

void Renderer::cleanup()
{
}

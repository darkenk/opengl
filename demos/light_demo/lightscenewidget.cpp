/**
 * Copyright (C) 2015, Dariusz Kluska <darkenk@gmail.com>
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
#include "lightscenewidget.hpp"
#include <vector>
#include <utility>
#include "shader.hpp"
#include "terrain.hpp"
#include "colouredobject.hpp"
#include "cube.hpp"

using namespace std;

LightSceneWidget::LightSceneWidget(QWidget* _parent) :
    MyGLWidget(_parent)
{

}

void LightSceneWidget::initScene()
{
    vector<pair<GLuint, const string>> shaders{
        pair<GLuint, const string>(GL_FRAGMENT_SHADER, "opengl_shaders/fragment.glsl"),
        pair<GLuint, const string>(GL_VERTEX_SHADER, "opengl_shaders/vertex.glsl")};
    shared_ptr<Shader> shader = make_shared<Shader>(shaders);
    getRenderer().getLight()->addShader(shader);
    getRenderer().addObject(make_shared<ColouredObject>(make_shared<Cube>(), shader));
    auto object = make_shared<ColouredObject>(make_shared<Terrain>(1024, 1024), shader);
    glm::mat4 m = glm::translate(glm::mat4(), glm::vec3(-12.0f, -3.0f, -24.0f));
    object->setModel(m);
    getRenderer().addObject(object);
}

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
#include <QApplication>
#include <string>
#include "utils/utils.hpp"
#include "myglwidget.hpp"
#include "utils/make_unique.hpp"
#include "simpleobject.hpp"
#include "models/cube.hpp"
#include "models/terrain.hpp"

using namespace std;

void initScene(Renderer& renderer) {
    vector<pair<GLuint, const string>> shaders{
        make_pair(GL_FRAGMENT_SHADER, "triangle_shaders/fragment.glsl"),
        make_pair(GL_VERTEX_SHADER, "triangle_shaders/vertex.glsl")};
    auto shader = make_shared<Shader>(shaders);
    auto triangle = make_unique<Triangle>();
    auto triangleVert = make_shared<Buffer<Vertex3>>(triangle->getVertices());
    auto triangleIdx = make_shared<Buffer<Index, GL_ELEMENT_ARRAY_BUFFER>>(triangle->getIndices());
    auto triangleObject = make_shared<SimpleObject>(triangleVert, triangleIdx, shader);
    renderer.addObject(triangleObject);
}

int main(int argc, char *argv[])
{
    {
        string s(argv[0]);
        s.erase(s.find_last_of("/")+1);
        setBasePath(s);
    }
    QApplication app(argc, argv);
    MyGLWidget widget(nullptr, initScene);
    widget.show();
    return app.exec();
}

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
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <memory>
#include <string>

#include "renderer.hpp"
#include "shader.hpp"
#include "logger.hpp"
#include "utils.hpp"

using namespace std;

static const char* WINDOW_TITLE{"OpenGL"};
static constexpr int INITIAL_WIDTH{800};
constexpr int INITIAL_HEIGHT{600};

static Renderer* gRenderer;

static void render()
{
    gRenderer->render();
    glutSwapBuffers();
    glutPostRedisplay();
}

static void cleanup()
{
    gRenderer->cleanup();
}

static void resize(int width, int height)
{
    gRenderer->resize(width, height);
}

static void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
    gRenderer->handleKey(key);
}

int main(int argc, char* argv[])
{
    {
        string s(argv[0]);
        s.find_last_not_of("/");
        s.erase(s.find_last_of("/")+1);
        setBasePath(s);
    }
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(render);
    glutCloseFunc(cleanup);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);

    gRenderer = new Renderer();
    gRenderer->resize(INITIAL_WIDTH, INITIAL_HEIGHT);

    glutMainLoop();
    delete gRenderer;
    gRenderer = nullptr;
    return 0;
}


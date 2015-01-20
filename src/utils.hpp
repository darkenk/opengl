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
#ifndef UTILS_H
#define UTILS_H

#include <GL/glew.h>

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <ostream>

struct Vertex
{
    Vertex() {}
    Vertex(glm::vec4 pos, glm::vec4 col = glm::vec4{1.0f, 1.0f, 0.2f, 1.0f},
           glm::vec4 nor = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}) :
        position(pos), color(col), normal(nor) {}
    glm::vec4 position;
    glm::vec4 color;
    glm::vec4 normal;
    friend std::ostream& operator<<(std::ostream& of, const Vertex& v) {
        return of << "Vertex " << v.position.x << ", " << v.position.y << ", "
                  << v.position.z << ", " << v.position.w;
    }
};

struct DirectionalLight
{
    glm::vec4 color;
    float ambientIntensity;
};

typedef std::vector<Vertex> VertexVector;
typedef std::shared_ptr<VertexVector> VertexVectorPtr;

typedef unsigned int Index;
typedef std::vector<Index> IndexVector;
typedef std::shared_ptr<IndexVector> IndexVectorPtr;

std::string getBasePath();
void setBasePath(const std::string& path);

GLint convertGLTypeToSize(GLenum type);
void checkGlError(const char* funcName);

#endif // UTILS_H

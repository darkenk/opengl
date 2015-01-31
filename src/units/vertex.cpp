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
#include "vertex.hpp"
#include "logger.hpp"

using namespace std;

const array<const uint32_t, 3> Vertex::desc{
    offsetof(Vertex, position),
    offsetof(Vertex, color),
    offsetof(Vertex, normal)};

void Vertex::rotateX(const Radians& angle) {
    position = Position{glm::rotateX(position, static_cast<float>(angle))};
    normal = Vector{glm::rotateX(normal, static_cast<float>(angle))};
}

void Vertex::rotateY(const Radians& angle) {
    position = Position{glm::rotateY(position, static_cast<float>(angle))};
    normal = Vector{glm::rotateY(normal, static_cast<float>(angle))};
}

void Vertex::rotateZ(const Radians& angle) {
    position = Position{glm::rotateZ(position, static_cast<float>(angle))};
    normal = Vector{glm::rotateZ(normal, static_cast<float>(angle))};
}

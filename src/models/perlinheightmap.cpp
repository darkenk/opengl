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
#include "perlinheightmap.hpp"
#include <glm/gtc/noise.hpp>
#include <cinttypes>

using namespace std;

PerlinHeightMap::PerlinHeightMap(uint32_t w, uint32_t h):
    HeightMap(w, h),
    mOctaves{7}
{
    generate();
}

PerlinHeightMap::~PerlinHeightMap()
{
}

void PerlinHeightMap::generate()
{
    float w = width();
    float h = height();
    for (uint32_t y = 0; y < height(); y++) {
        for (uint32_t x = 0; x < width(); x++) {
            mHeightMap[y][x] = octave(x/w, y/h);
        }
    }
}

float PerlinHeightMap::octave(float x, float y)
{
    float total = 0;
    float frequency = 1;
    float amplitude = 1;
    float persistence = 0.9f;
    for (uint32_t i = 0;i < mOctaves; i++) {
        total += glm::perlin(glm::vec2(x * frequency, y * frequency)) * amplitude;
        amplitude *= persistence;
        frequency *= 2;
    }
    return total;
}

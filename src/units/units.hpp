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
#ifndef UNITS_HPP
#define UNITS_HPP

#include <glm/glm.hpp>
#include <glm/gtx/constants.hpp>
#include <ostream>
#include <GL/glew.h>

class Radians
{
public:
    explicit constexpr Radians(const float radians) : mAngle(radians) {}
    explicit operator float() const { return mAngle; }

    template<typename T>
    Radians operator/(const T v) const { return Radians{mAngle / static_cast<float>(v)}; }

    template<typename T>
    Radians operator*(const T v) const { return Radians{mAngle * static_cast<float>(v)}; }

private:
    float mAngle;
};

constexpr Radians PI{3.14159265358979323846264338327950288f};

template<int M, int K, int S>
struct Unit
{
    // a unit in the MKS system
    enum {m=M, kg=K, s=S};
};

template<typename Unit> // a magnitude with a unit
struct Value
{
    float val; // the magnitude
    constexpr explicit Value(float d) : val(d) {}
    constexpr explicit Value(long double d) : val(static_cast<float>(d)) {}
    constexpr explicit Value(unsigned int d) : val(static_cast<float>(d)) {}
    explicit operator float() const { return val; }
    Value operator-() { val = -val; return *this; }
};

using Speed = Value<Unit<1, 0, -1>>; // meters/second type
using Acceleration = Value<Unit<1, 0, -2>>;
using Meter = Value<Unit<1, 0, 0>>;

using Second = Value<Unit<0, 0, 1>>; // unit:sec
using Second2 = Value<Unit<0, 0, 2>>; // unit: second*second

constexpr Second operator"" _s(long double d) { return Second(d); }

constexpr Meter operator"" _m(long double d) { return Meter(d); }

class Position : public glm::vec4
{
public:
    explicit Position(Meter _x = 0.0_m, Meter _y = 0.0_m, Meter _z = 0.0_m) :
        glm::vec4{_x, _y, _z, 1.0f} {}
    explicit Position(glm::vec4& v) : glm::vec4{v} {}
    explicit Position(glm::vec4&& v) : glm::vec4{v} {}
    explicit Position(glm::vec3 v) : glm::vec4{v.x, v.y, v.z, 1.0f} {}
    friend std::ostream& operator<<(std::ostream& o, const Position& p) {
        return o << "p(" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ")";
    }
    static constexpr GLenum Type = GL_FLOAT;
    static constexpr GLint Size = 4;
};

class Color : public glm::vec4
{
public:
    explicit Color(float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f) :
        glm::vec4{_r, _g, _b, _a} {}
    friend std::ostream& operator<<(std::ostream& o, const Color& c) {
        return o << "c(" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ")";
    }
    static constexpr GLenum Type = GL_FLOAT;
    static constexpr GLint Size = 4;
};

class Vector : public glm::vec4
{
public:
    explicit Vector(float _x = 1.0f, float _y = 0.0f, float _z = 0.0f) :
        glm::vec4{_x, _y, _z, 0.0f} {}
    explicit Vector(glm::vec4& v) : glm::vec4{v} {}
    explicit Vector(glm::vec4&& v) : glm::vec4{v} {}
    explicit Vector(const glm::vec3& v) : glm::vec4{v, 0.0f} {}
    friend std::ostream& operator<<(std::ostream& o, const Vector& d) {
        return o << "v(" << d.x << ", " << d.y << ", " << d.z << ", " << d.w << ")";
    }
    static constexpr GLenum Type = GL_FLOAT;
    static constexpr GLint Size = 4;
};

class UV : public glm::vec2
{
public:
    explicit UV(float _x = 1.0f, float _y = 0.0f) : glm::vec2{_x, _y} {}
    static constexpr GLenum Type = GL_FLOAT;
    static constexpr GLint Size = 2;
};

#endif // UNITS_HPP

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
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>
#include <cstdio>
#include <glm/glm.hpp>

inline std::ostream& operator<<(std::ostream& o, const glm::vec4& v) {
    return o << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}

inline std::ostream& operator<<(std::ostream& o, const glm::vec3& v) {
    return o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

inline std::ostream& operator<<(std::ostream& o, const glm::vec2& v) {
    return o << "(" << v.x << ", " << v.y << ")";
}

class Logger
{
public:
    enum Level {
        Verbose,
        Debug,
        Error
    };

    Logger(Level level): mLevel(level) {}
    ~Logger() { std::cerr << std::endl; }

    template<class T>
    Logger& operator<<(T var) {
        std::cerr << getColor() << var << "\033[0m";
        return *this;
    }

private:
    Level mLevel;
    const char* getColor();
};

#define LOG(level) Logger(level) << __FILENAME__ << ":" << __LINE__ << " "
#define LOGV LOG(Logger::Level::Verbose)
#define LOGD LOG(Logger::Level::Debug)
#define LOGE LOG(Logger::Level::Error)

#define LOGP(color, fmt, ...) printf(color "%s:%d " fmt "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#define LOGVP(fmt, ...) LOGP("\033[32m", fmt, ##__VA_ARGS__)
#define LOGVD(fmt, ...) LOGP("\033[33m", fmt, ##__VA_ARGS__)
#define LOGVE(fmt, ...) LOGP("\033[31m", fmt, ##__VA_ARGS__)

#endif // LOGGER_HPP

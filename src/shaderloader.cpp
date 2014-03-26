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
#include "shaderloader.hpp"
#include <fstream>
#include <iomanip>

std::string ShaderLoader::mLaunchedPath = "";

ShaderLoader::ShaderLoader() :
    mContent(nullptr)
{
}

ShaderLoader::~ShaderLoader()
{
    delete mContent;
    mContent = nullptr;
}

bool ShaderLoader::loadShader(const char *fileName)
{
    std::string s(mLaunchedPath);
    s.append(fileName);
    std::ifstream file(s);
    if (!file.good()) {
        file.close();
        return false;
    }
    file.seekg (0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    mContent = new char[size+1];
    mContent[size] = '\0';
    file.read(mContent, size);
    file.close();
    return true;
}

const char* ShaderLoader::getShader()
{
    return mContent;
}

void ShaderLoader::releaseShader()
{
    delete[] mContent;
    mContent = nullptr;
}

void ShaderLoader::setLaunchedPath(std::string &s)
{
    mLaunchedPath = s;
}
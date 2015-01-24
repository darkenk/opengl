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
#include "vectorsetter.hpp"
#include "ui_vectorsetter.h"

using namespace std;

VectorSetter::VectorSetter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VectorSetter)
{
    ui->setupUi(this);
    connect(ui->x, SIGNAL(valueChanged(float)), this, SLOT(onXValueChanged(float)));
    connect(ui->y, SIGNAL(valueChanged(float)), this, SLOT(onYValueChanged(float)));
    connect(ui->z, SIGNAL(valueChanged(float)), this, SLOT(onZValueChanged(float)));
    connect(ui->w, SIGNAL(valueChanged(float)), this, SLOT(onWValueChanged(float)));
}

VectorSetter::~VectorSetter()
{
    delete ui;
}

void VectorSetter::setValue(const glm::vec4& vec)
{
    mVectorValue = vec;
    ui->x->setValue(vec.x);
    ui->y->setValue(vec.y);
    ui->z->setValue(vec.z);
    ui->w->setValue(vec.w);
}

void VectorSetter::setValuesNames(const vector<const char*>& names)
{
    ui->x->setName(names[0]);
    ui->y->setName(names[1]);
    ui->z->setName(names[2]);
    ui->w->setName(names[3]);
}

void VectorSetter::setName(const char* name)
{
    ui->groupBox->setTitle(name);
}

void VectorSetter::setRange(const vector<pair<float, float>>& range)
{
    ui->x->setRange(range[0].first, range[0].second);
    ui->y->setRange(range[1].first, range[1].second);
    ui->z->setRange(range[2].first, range[2].second);
    ui->w->setRange(range[3].first, range[3].second);
}

void VectorSetter::onXValueChanged(float v)
{
    mVectorValue.x = v;
    emit vectorChanged(&mVectorValue);
}

void VectorSetter::onYValueChanged(float v)
{
    mVectorValue.y = v;
    emit vectorChanged(&mVectorValue);
}

void VectorSetter::onZValueChanged(float v)
{
    mVectorValue.z = v;
    emit vectorChanged(&mVectorValue);
}

void VectorSetter::onWValueChanged(float v)
{
    mVectorValue.w = v;
    emit vectorChanged(&mVectorValue);
}

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
#include "valueslider.hpp"
#include "ui_valueslider.h"

ValueSlider::ValueSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueSlider)
{
    ui->setupUi(this);
    mMaxValue = ui->horizontalSlider->maximum();
}

ValueSlider::~ValueSlider()
{
    delete ui;
}

void ValueSlider::setName(const QString& name)
{
    ui->label->setText(name);
}

void ValueSlider::setRange(float min, float max)
{
    ui->horizontalSlider->setMaximum(static_cast<int>(max * mMaxValue));
    ui->horizontalSlider->setMinimum(static_cast<int>(min * mMaxValue));
}

void ValueSlider::setValue(float value)
{
    ui->horizontalSlider->setValue(static_cast<int>(value * mMaxValue));
}

void ValueSlider::on_horizontalSlider_valueChanged(int value)
{
    float v = value/mMaxValue;
    ui->value->setValue(v);
    emit valueChanged(v);
}

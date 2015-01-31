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
#include "lightsettings.hpp"
#include "ui_lightsettings.h"

using namespace std;

LightSettings::LightSettings(QWidget *_parent) :
    QWidget(_parent, Qt::Widget),
    ui(new Ui::LightSettings)
{
    ui->setupUi(this);
    ui->mAmbientLightIntensity->setName("Ambient intensity");
    ui->mAmbientLightColor->setName("Ambient Light Color");
    ui->mDiffuseDirection->setName("Diffuse direction");
    ui->mDiffuseIntensity->setName("Diffuse intensity");

    vector<const char*> colorNames{"Red", "Green", "Blue", "Alpha"};
    ui->mAmbientLightColor->setValuesNames(colorNames);
    connect(ui->mAmbientLightIntensity, SIGNAL(valueChanged(float)), this,
            SLOT(onAmbientIntensityChanged(float)));
    connect(ui->mAmbientLightColor, SIGNAL(vectorChanged(glm::vec4*)), this,
            SLOT(onColorChanged(glm::vec4*)));
    vector<const char*> xyzNames{"x", "y", "z", "w"};
    ui->mDiffuseDirection->setValuesNames(xyzNames);
    connect(ui->mDiffuseDirection, SIGNAL(vectorChanged(glm::vec4*)), this,
            SLOT(onDiffuseDirectionChanged(glm::vec4*)));
    connect(ui->mDiffuseIntensity, SIGNAL(valueChanged(float)), this,
            SLOT(onDiffuseIntensityChanged(float)));
    vector<pair<float, float>> diffuseRange{{-1.0f, 1.0f}, {-1.0f, 1.0f}, {-1.0f, 1.0f},
                                            {-1.0f, 1.0f}};
    ui->mDiffuseDirection->setRange(diffuseRange);
}

LightSettings::~LightSettings()
{
    delete ui;
}

void LightSettings::setLight(std::shared_ptr<Light> light)
{
    mLight = light;
    ui->mAmbientLightIntensity->setValue(light->getAmbientIntensity());
    ui->mAmbientLightColor->setValue(light->getAmbientColor());
    ui->mDiffuseDirection->setValue(light->getDiffuseDirection());
    ui->mDiffuseIntensity->setValue(light->getDiffuseIntensity());
}

void LightSettings::onAmbientIntensityChanged(float v)
{
    mLight->setAmbientIntensity(v);
}

void LightSettings::onColorChanged(glm::vec4* color)
{
    mLight->setAmbientColor(*color);
}

void LightSettings::onDiffuseDirectionChanged(glm::vec4* direction)
{
    mLight->setDiffuseDirection(*direction);
}

void LightSettings::onDiffuseIntensityChanged(float v)
{
    mLight->setDiffuseIntensity(v);
}

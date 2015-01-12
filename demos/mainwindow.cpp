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
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow}
{
    ui->setupUi(this);
    ui->mAmbientLightIntensity->setName("Ambient intensity");
    ui->mRedColor->setName("Red");
    ui->mGreenColor->setName("Green");
    ui->mBlueColor->setName("Blue");
    ui->mAlpha->setName("Alpha");
    connect(ui->mAmbientLightIntensity, SIGNAL(valueChanged(float)), this,
                                               SLOT(onAmbientIntensityChanged(float)));
    connect(ui->mRedColor, SIGNAL(valueChanged(float)), this, SLOT(onRedColorChanged(float)));
    connect(ui->mGreenColor, SIGNAL(valueChanged(float)), this, SLOT(onGreenColorChanged(float)));
    connect(ui->mBlueColor, SIGNAL(valueChanged(float)), this, SLOT(onBlueColorChanged(float)));
    connect(ui->mAlpha, SIGNAL(valueChanged(float)), this, SLOT(onAlphaChanged(float)));
    connect(ui->mRenderWindow, SIGNAL(initialized()), this, SLOT(onGLInitialized()));
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
}

void MainWindow::onGLInitialized()
{
    Light& light = ui->mRenderWindow->getRenderer().getLight();
    float m = ui->mAmbientLightIntensity->getMaxValue();
    ui->mAmbientLightIntensity->setValue(static_cast<int>(light.getAmbientIntensity() * m));
    mAmbientLightColor = light.getAmbientColor();
    m = ui->mBlueColor->getMaxValue();
    ui->mBlueColor->setValue(static_cast<int>(mAmbientLightColor.b * m));
    ui->mGreenColor->setValue(static_cast<int>(mAmbientLightColor.g * m));
    ui->mRedColor->setValue(static_cast<int>(mAmbientLightColor.r * m));
    ui->mAlpha->setValue(static_cast<int>(mAmbientLightColor.a * m));
}

void MainWindow::onAmbientIntensityChanged(float v)
{
    ui->mRenderWindow->getRenderer().getLight().setAmbientIntensity(v);
}

void MainWindow::onRedColorChanged(float v)
{
    mAmbientLightColor.r = v;
    updateAmbientLightColor();
}

void MainWindow::onGreenColorChanged(float v)
{
    mAmbientLightColor.g = v;
    updateAmbientLightColor();
}

void MainWindow::onBlueColorChanged(float v)
{
    mAmbientLightColor.b = v;
    updateAmbientLightColor();
}

void MainWindow::onAlphaChanged(float v)
{
    mAmbientLightColor.a = v;
    updateAmbientLightColor();
}

void MainWindow::updateAmbientLightColor()
{
    ui->mRenderWindow->getRenderer().getLight().setAmbientColor(mAmbientLightColor);
}

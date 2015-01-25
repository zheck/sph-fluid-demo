//
//  Keyboard.cpp
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include <GLUT/GLUT.h>

#include "Keyboard.h"
#include "SphFluidDemo.h"
#include "config.h"

Keyboard::Keyboard()
{
    _cameraFuncs['i'] = &Keyboard::zoomIn;
    _cameraFuncs['o'] = &Keyboard::zoomOut;
    _cameraFuncs['f'] = &Keyboard::rotateRight;
    _cameraFuncs['s'] = &Keyboard::rotateLeft;
    _cameraFuncs['e'] = &Keyboard::rotateUp;
    _cameraFuncs['d'] = &Keyboard::rotateDown;
}

Keyboard::~Keyboard()
{}

void Keyboard::update(unsigned char key, int x, int y)
{
    if (_cameraFuncs.find(key) != _cameraFuncs.end())
        (this->*_cameraFuncs[key])();
}

void Keyboard::zoomIn()
{
    SphFluidDemo::instance()->camera.zoomIn();
}

void Keyboard::zoomOut()
{
    SphFluidDemo::instance()->camera.zoomOut();
}

void Keyboard::rotateLeft()
{
    SphFluidDemo::instance()->camera.rotate(-ROTATION_SCALE);
}

void Keyboard::rotateRight()
{
    SphFluidDemo::instance()->camera.rotate(ROTATION_SCALE);
}

void Keyboard::rotateUp()
{
    SphFluidDemo::instance()->camera.verticalRotate(ROTATION_SCALE);
}

void Keyboard::rotateDown()
{
    SphFluidDemo::instance()->camera.verticalRotate(-ROTATION_SCALE);
}
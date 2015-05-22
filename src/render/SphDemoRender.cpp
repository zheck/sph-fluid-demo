//
//  SphDemoRender.cpp
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include <GLUT/GLUT.h>

#include "SphDemoRender.h"
#include "SphFluidDemo.h"

SphDemoRender::SphDemoRender()
{}

SphDemoRender::~SphDemoRender()
{}

void SphDemoRender::init()
{
}

void SphDemoRender::render(FluidBody &fluidBody, Glass &glass)
{
    for (std::list<Particle *>::iterator it = fluidBody.particles().begin(); it != fluidBody.particles().end(); ++it) {
        _particleRender.render(*it);
    }
    _glassRender.render(glass);
    _debugRender.render();
}

//
//  FluidBody.cpp
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "FluidBody.h"
#include "Grid.h"

FluidBody::FluidBody()
{}

FluidBody::~FluidBody()
{
    for (std::list<Particle *>::iterator it = _particles.begin(); it != _particles.end(); ++it) {
        delete *it;
    }
    _particles.clear();
}

std::list<Particle *> & FluidBody::getParticles()
{
    return _particles;
}

void FluidBody::addParticle(Particle *particle)
{
    _particles.push_back(particle);
}

//
//  Particle.cpp
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "Particle.h"

Particle::Particle(Vect3f const & pos) :
_position(pos)
{
}

Particle::~Particle()
{
}

Vect3f & Particle::getPosition()
{
    return _position;
}
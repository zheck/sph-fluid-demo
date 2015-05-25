//
//  Particle.cpp
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//
#include <GLUT/GLUT.h>

#include "Particle.h"
#include "config.h"

Particle::Particle(const Vect3f& pos) :
position(pos)
{}

Particle::~Particle()
{}

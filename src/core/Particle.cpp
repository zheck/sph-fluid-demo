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

Particle::Particle(const Vect3f& position, int particleId) :
_position(position)
{
    myQuadric = NULL;
    _id = particleId;
}

Particle::~Particle()
{}

void Particle::draw()
{
    glPushMatrix();
    
    glColor3f(0.01, 0.26, 1.0);
    glTranslated(_position.x, _position.y, _position.z);
    glutSolidSphere(PARTICLE_RENDER_RADIUS, 10, 10);
    
    glPopMatrix();
}

//#include "Particle.h"
//
//Particle::Particle(Vect3f const & pos) :
//position(pos),
//velocity(0, 0, 0)
//{
//}
//
//Particle::~Particle()
//{
//}

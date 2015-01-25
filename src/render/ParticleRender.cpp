//
//  ParticleRender.cpp
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include <GLUT/GLUT.h>

#include "config.h"
#include "ParticleRender.h"
#include "Vect3f.h"

ParticleRender::ParticleRender()
{}

ParticleRender::~ParticleRender()
{}

void ParticleRender::render(Particle * particle)
{
    glPushMatrix();

    glColor3f(0.12, 0.7, 1);
    glTranslatef(particle->getPosition().x, particle->getPosition().y, particle->getPosition().z);
    glutSolidSphere(PARTICLE_RENDER_RADIUS, 20, 20);

    glPopMatrix();
}

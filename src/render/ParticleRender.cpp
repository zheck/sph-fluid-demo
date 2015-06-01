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
    glTranslatef(particle->position.x, particle->position.y, particle->position.z);
    glutSolidSphere(PARTICLE_RENDER_RADIUS, 10, 10);

    glPopMatrix();
}

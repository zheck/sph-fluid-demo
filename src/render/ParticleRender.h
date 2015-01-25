//
//  ParticleRender.h
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__ParticleRender__
#define __sph_fluid__ParticleRender__

#include <stdio.h>

#include "Particle.h"

class ParticleRender
{
public:
    ParticleRender();
    ParticleRender(ParticleRender const & rhs);
    ~ParticleRender();

    ParticleRender & operator=(ParticleRender const & rhs);

    void render(Particle * particle);
};

#endif /* defined(__sph_fluid__ParticleRender__) */

//
//  FluidBody.h
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__FluidBody__
#define __sph_fluid__FluidBody__

#include <stdio.h>
#include <list>

#include "Particle.h"
#include "Grid.h"

class FluidBody
{
    std::list<Particle *> _particles;

public:
    FluidBody();
    FluidBody(FluidBody const & rhs);
    ~FluidBody();

    FluidBody & operator=(FluidBody const & rhs);

    std::list<Particle *> & particles();
    void addParticle(Particle *particle);
};

#endif /* defined(__sph_fluid__FluidBody__) */

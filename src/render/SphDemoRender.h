//
//  SphDemoRender.h
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__SphDemoRender__
#define __sph_fluid__SphDemoRender__

#include <stdio.h>
#include <vector>

#include "Particle.h"
#include "ParticleRender.h"
#include "DebugRender.h"
#include "GridRender.h"

class SphDemoRender
{
    ParticleRender _particleRender;
    DebugRender _debugRender;
    GridRender _gridRender;

public:
    SphDemoRender();
    SphDemoRender(SphDemoRender const & rhs);
    ~SphDemoRender();

    SphDemoRender & operator=(SphDemoRender const & rhs);

    void init();
    void render();
};

#endif /* defined(__sph_fluid__SphDemoRender__) */

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

#include "FluidBody.h"
#include "Glass.h"
#include "ParticleRender.h"
#include "DebugRender.h"
#include "GlassRender.h"

class SphDemoRender
{
    ParticleRender _particleRender;
    DebugRender _debugRender;
    GlassRender _glassRender;

public:
    SphDemoRender();
    SphDemoRender(SphDemoRender const & rhs);
    ~SphDemoRender();

    SphDemoRender & operator=(SphDemoRender const & rhs);

    void init();
    void render(FluidBody & fluidBody, Glass & glass);
};

#endif /* defined(__sph_fluid__SphDemoRender__) */

//
//  SphFluidDemo.h
//  sph-fluid
//
//  Created by zhou on 12/6/14.
//  Copyright (c) 2014 zhou. All rights reserved.
//

#ifndef __sph_fluid__SphFluidDemo__
#define __sph_fluid__SphFluidDemo__


#include <vector>

#include "config.h"
#include "Singleton.h"
#include "Camera.h"
#include "Keyboard.h"
#include "FluidBody.h"
#include "Grid.h"
#include "Particle.h"

class SphFluidDemo : public Singleton<SphFluidDemo>
{
public:
    Camera camera;
    Keyboard keyboard;
    Grid grid;
    FluidBody fluidBody;
    
public:
    SphFluidDemo();
    SphFluidDemo(SphFluidDemo const & rhs);
    ~SphFluidDemo();

    SphFluidDemo & operator=(SphFluidDemo const & rhs);

    void update();
    void draw();
    
protected:
    void step1();
    void step2();
    void collisions(Particle * particle);
};

#endif /* defined(__sph_fluid__SphFluidDemo__) */

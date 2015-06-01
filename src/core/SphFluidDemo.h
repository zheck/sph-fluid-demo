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
#include "UniformGrid.h"
#include "Particle.h"
#include "Glass.h"
#include "SphDemoRender.h"

class SphFluidDemo : public Singleton<SphFluidDemo>
{
    int _numberOfParticle;
    FluidBody _fluidBody;
    UniformGrid _uniformGrid;
    Glass *_glass;
    std::vector<Particle *> _neighbors; // a temporary array to be filled with neighbors of a particle
    int _currentFPS;

public:
    Camera camera;
    Keyboard keyboard;
    SphDemoRender render;

public:
    SphFluidDemo();
    SphFluidDemo(SphFluidDemo const & rhs);
    ~SphFluidDemo();

    SphFluidDemo & operator=(SphFluidDemo const & rhs);

    void update();
    void draw();

    int fps() const;
    int numberOfParticle() const;

protected:
    void generateParticles();
    void step1();
    void step2();
};

#endif /* defined(__sph_fluid__SphFluidDemo__) */

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

#include "Particle.h"
#include "Grid.h"
#include "Wall.h"


#include "config.h"
#include "Singleton.h"
#include "Camera.h"
#include "Keyboard.h"

using namespace std;

class SphFluidDemo : public Singleton<SphFluidDemo>
{
public:
    Camera camera;
    Keyboard keyboard;
    
public:
    void init();
    
private:
    vector<Particle> _particles;
    vector<Wall>     _walls;
    Vect3f boxSize;
    int _numberOfParticle;
    
public:
    Grid* grid;
    double surfaceThreshold;
    Vect3f gravityVector;
    
public:
    SphFluidDemo();
    ~SphFluidDemo();


    void updateGrid();
    void draw();
    void update();
    
protected:
    void pressureEngine();
    void physicsEngine();
    void collisionForce(Particle& particle);
};

//#include <iostream>
//
//#include "Singleton.h"
//#include "Keyboard.h"
//#include "Camera.h"
//#include "Mouse.h"
//#include "FluidBody.h"
//#include "SphDemoRender.h"
//#include "Grid.h"
//
//class SphFluidDemo : public Singleton<SphFluidDemo>
//{
//public:
//    Camera camera;
//    Keyboard keyboard;
//    Mouse mouse;
//    Grid grid;
//
//    FluidBody fluidBody;
//    SphDemoRender renderer;
//
//public:
//    SphFluidDemo();
//    SphFluidDemo(SphFluidDemo const & rhs);
//    ~SphFluidDemo();
//
//    SphFluidDemo & operator=(SphFluidDemo const & rhs);
//
//    void init();
//    void update();
//    void display();
//
//protected:
//    void step1(); // pressure
//    void step2(); // forces
//    void collisions(Particle & particle);
//};

#endif /* defined(__sph_fluid__SphFluidDemo__) */
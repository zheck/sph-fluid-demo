//
//  SphFluidDemo.cpp
//  sph-fluid
//
//  Created by zhou on 12/6/14.
//  Copyright (c) 2014 zhou. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <iostream>

#include "SphFluidDemo.h"
#include "config.h"

SphFluidDemo::SphFluidDemo() :
grid(Vect3f(0, 0, 0), Vect3f(GRID_SIZE, GRID_SIZE, GRID_SIZE)),
camera(1.5, 20, 70)
{
    std::cout << "demo started" << std::endl;
}

SphFluidDemo::~SphFluidDemo()
{
    std::cout << "demo finished" << std::endl;
}

void SphFluidDemo::init()
{
    renderer.init();
    Vect3f eye = grid.getCenter() * 0.5;
    camera.init(eye, grid.getCenter(), Vect3f(0, 1, 0));

    int numberOfParticle = 0;
    for (float x = 0; x < grid.dimension().x; x += 2 * PARTICLE_RADIUS) {
        for (float z = 0; z < grid.dimension().z; z += 2 * PARTICLE_RADIUS) {
            for (float y = 0; y < grid.dimension().y; y += 2 * PARTICLE_RADIUS) {
                if (++numberOfParticle > MAX_PARTICLE) {
                    break;
                }
                Particle *p = new Particle(Vect3f(x, y, z));
                fluidBody.addParticle(p);
                grid(0, 0, 0).push_back(p);
            }
        }
    }
    grid.update();
}

void SphFluidDemo::update()
{}

void SphFluidDemo::display()
{
    renderer.render();
}

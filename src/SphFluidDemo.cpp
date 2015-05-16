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
#include "sph_formulas.h"

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
{
    step1();
    step2();

    float dt = 1.0 / 100.0;
    std::list<Particle *> particles = fluidBody.getParticles();
    for (std::list<Particle *>::iterator it = particles.begin(); it != particles.end(); ++it) {
        Vect3f position = (*it)->position;
        Vect3f velocity = (*it)->velocity * dt;
        Vect3f acceleration = (*it)->acceleration * dt * dt;
        Vect3f newPosition = position + velocity + acceleration;
        Vect3f newVelocity = (newPosition - (*it)->position) / dt;;

        (*it)->position = newPosition;
        (*it)->velocity = newVelocity;
    }

    grid.update();
}

// update density and pressure for each particle
void SphFluidDemo::step1()
{
    std::list<Particle *> particles = fluidBody.getParticles();
    for (std::list<Particle *>::iterator particle = particles.begin(); particle != particles.end(); ++particle) {
        float kernels = 0.0;
        std::list<Particle *> * neightborParticles = grid.getNeighborParticles(**particle);
        for (std::list<Particle *>::iterator it = neightborParticles->begin(); it != neightborParticles->end(); ++it) {
            Vect3f distance = (*particle)->position - (*it)->position;
            kernels += wpoly6Kernel(distance.dot(distance));
        }
        (*particle)->density = kernels * PARTICLE_MASS;
        (*particle)->pressure = WATER_STIFFNESS * ((*particle)->density - PARTICLE_DENSITY_REST); //pressure = k(ρ − ρ0);
        neightborParticles->clear();
        delete neightborParticles;
    }
}


void SphFluidDemo::step2()
{
    std::list<Particle *> particles = fluidBody.getParticles();
    for (std::list<Particle *>::iterator particle = particles.begin(); particle != particles.end(); ++particle) {
        std::list<Particle *> * neightborParticles = grid.getNeighborParticles(**particle);
        Vect3f f_pressure, f_viscosity, f_surface, colorField;
        Vect3f f_gravity(0, GRAVITY, 0);
        float colorFieldLaplacian = 0.0;
        
        for (std::list<Particle *>::iterator it = neightborParticles->begin(); it != neightborParticles->end(); ++it) {
            Vect3f distance = (*particle)->position - (*it)->position;
            float dotRadius = distance.dot(distance);
            if (dotRadius < PARTICLE_RADIUS_SQUARE) {
                Vect3f poly6Gradient = wpoly6KernelGradient(dotRadius, distance);
                Vect3f spikyGradient = spikyKernelGradient(dotRadius, distance);
                if (*it != *particle) {
                    f_pressure += noSymmetricalPressure((*particle)->pressure, (*particle)->density, (*it)->pressure, (*it)->density, spikyGradient);
                    f_viscosity += noSymmetricalViscosity((*particle)->velocity, (*it)->velocity, (*it)->density, viscosityKernel(dotRadius));
                }
                colorField += poly6Gradient / (*it)->density * PARTICLE_MASS;
                colorFieldLaplacian += wpoly6KernelSecond(dotRadius) / (*it)->density * PARTICLE_MASS;
            }
        }
        
        (*particle)->normal = colorField * -1;
        float colorFieldNormalMagnitude = colorField.magnitude();
        if (colorFieldNormalMagnitude > SURFACE_THRESHOLD) {
            f_surface = colorField / colorFieldNormalMagnitude * colorFieldLaplacian * -SURFACE_TENSION;
        }
        (*particle)->acceleration = (f_pressure + f_viscosity + f_surface + f_gravity) / (*particle)->density;
        collisions(**particle);

        neightborParticles->clear();
        delete neightborParticles;
    }
}

void SphFluidDemo::collisions(Particle & particle)
{
    std::list<Wall *> walls = grid.getWalls();

    for (std::list<Wall *>::iterator it = walls.begin(); it != walls.end(); ++it) {
        Vect3f center = (*it)->center;
        Vect3f normal = (*it)->normal;
        float d = (center - particle.position).dot(normal) + 0.01;
        if (d > 0.0) {
            particle.acceleration += normal * WALL_RESISTANCE * d;
            particle.acceleration += normal * particle.velocity.dot(normal) * WALL_DAMPING;
        }
    }
}

void SphFluidDemo::display()
{
    renderer.render();
}

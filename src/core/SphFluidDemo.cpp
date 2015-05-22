//
//  SphFluidDemo.cpp
//  sph-fluid
//
//  Created by zhou on 12/6/14.
//  Copyright (c) 2014 zhou. All rights reserved.
//

#include "SphFluidDemo.h"
#include "sph_formulas.h"

SphFluidDemo::SphFluidDemo() :
camera(CAMERA_ANGLE, CAMERA_DISTANCE, 70),
uniformGrid(Vect3f(0, 0, 0), Vect3f(GRID_SIZE, GRID_SIZE, GRID_SIZE))
{
    glass = new Glass(Vect3f(0, 0, 0), Vect3f(GLASS_SIDE_SIZE, GLASS_SIDE_SIZE, GLASS_SIDE_SIZE));
    camera.init(glass->center(), Vect3f(0, 1, 0));
    generateParticles();
    uniformGrid.update();
}

SphFluidDemo::~SphFluidDemo()
{}

void SphFluidDemo::generateParticles()
{
    int numberOfParticle = 0;


        for (float x = glass->origin().x; x < (glass->origin().x + glass->dimension().x); x += PARTICLE_RADIUS / 2) {
            for (float z = glass->origin().z; z < uniformGrid.origin().z + glass->dimension().z; z += PARTICLE_RADIUS / 2) {
                for (float y = glass->origin().y; y < uniformGrid.origin().y + glass->dimension().y; y += PARTICLE_RADIUS / 2) {

                if (numberOfParticle > MAX_PARTICLE) {
                    return;
                }
                Particle *p = new Particle(Vect3f(x, y, z));
                uniformGrid(0, 0, 0).push_back(p);
                fluidBody.addParticle(p);
                ++numberOfParticle;
            }
        }
    }
}

void SphFluidDemo::update()
{
    step1();
    step2();

    float dt = 1.0 / 100.0;
    for (std::list<Particle *>::iterator it = fluidBody.particles().begin(); it != fluidBody.particles().end(); ++it) {
        Vect3f newPosition = (*it)->position + (*it)->velocity * dt + (*it)->acceleration * dt * dt;
        Vect3f newVelocity = (newPosition - (*it)->position) / dt;

        (*it)->position = newPosition;
        (*it)->velocity = newVelocity;
    }

    uniformGrid.update();
}

// Update density and pressure for each particle
void SphFluidDemo::step1()
{
    for (std::list<Particle *>::iterator particle = fluidBody.particles().begin(); particle != fluidBody.particles().end(); ++particle) {
        float kernels = 0.0;

        std::list<Particle *> * neighborParticles = uniformGrid.getNeighborParticles(**particle);
        for (std::list<Particle *>::iterator it = neighborParticles->begin(); it != neighborParticles->end(); ++it) {
            Vect3f diffPosition = (*particle)->position - (*it)->position;
            kernels += wpoly6Kernel(diffPosition.dot(diffPosition));
        }

        (*particle)->density = kernels * PARTICLE_MASS;
        (*particle)->pressure = WATER_STIFFNESS * ((*particle)->density - PARTICLE_DENSITY_REST); //pressure = k(ρ − ρ0)
        neighborParticles->clear();
        delete neighborParticles;
    }
}

// Calculate external forces applied to each particles
// Interpretation of given sph formulas, see docs
void SphFluidDemo::step2()
{
    for (std::list<Particle *>::iterator particle = fluidBody.particles().begin(); particle != fluidBody.particles().end(); ++particle) {
        Vect3f f_pressure, f_viscosity, f_surface, colorField;
        Vect3f f_gravity(0, GRAVITY * (*particle)->density, 0);
        float colorFieldLaplacian = 0.0;

        std::list<Particle *> * neighborParticles = uniformGrid.getNeighborParticles(**particle);
        for (std::list<Particle *>::iterator it = neighborParticles->begin(); it != neighborParticles->end(); ++it) {
            Vect3f distance = (*particle)->position - (*it)->position;
            double dotRadius = distance.dot(distance);

            if (dotRadius <= PARTICLE_RADIUS_SQUARE) {
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
            f_surface = -SURFACE_TENSION * colorField / colorFieldNormalMagnitude * colorFieldLaplacian;
        }
        (*particle)->acceleration = (f_pressure + f_viscosity + f_gravity) / (*particle)->density;
        collisions(*particle);
        neighborParticles->clear();
        delete neighborParticles;
    }
}

void SphFluidDemo::collisions(Particle * particle) {
    std::list<Wall> walls = glass->getWalls();
    for (std::list<Wall>::iterator it = walls.begin(); it != walls.end(); ++it) {
        Vect3f center = (*it).center;
        Vect3f normal = (*it).normal;
        float f = (center - particle->position).dot(normal) + 0.01;
        
        if (f > 0.0) {
            particle->acceleration += GLASS_RESISTANCE * normal * f;
            particle->acceleration += GLASS_DAMPING * particle->velocity.dot(normal) * normal;
        }
    }
}

void SphFluidDemo::draw()
{
    render.render(fluidBody, *glass);
}

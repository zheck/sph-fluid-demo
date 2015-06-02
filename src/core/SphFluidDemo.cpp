//
//  SphFluidDemo.cpp
//  sph-fluid
//
//  Created by zhou on 12/6/14.
//  Copyright (c) 2014 zhou. All rights reserved.
//

#include <unistd.h>

#include "SphFluidDemo.h"
#include "sph_formulas.h"
#include "Timer.h"

SphFluidDemo::SphFluidDemo() :
_tp(4),
camera(CAMERA_ANGLE, CAMERA_DISTANCE, 70),
_uniformGrid(Vect3f(0, 0, 0), Vect3f(GRID_SIZE, GRID_SIZE, GRID_SIZE))
{
    _tp.init();
    _glass = new Glass(Vect3f(0, 0, 0), Vect3f(GLASS_SIDE_SIZE, GLASS_SIDE_SIZE, GLASS_SIDE_SIZE));
    camera.init(_glass->center(), Vect3f(0, 1, 0));
    generateParticles();
    _neighbors.resize(_numberOfParticle);
    _uniformGrid.update();
    step1();
    step2();
    _uniformGrid.update();
}

SphFluidDemo::~SphFluidDemo()
{}

void SphFluidDemo::generateParticles()
{
    _numberOfParticle = 0;

    for (float x = _glass->origin().x; x < (_glass->origin().x + _glass->dimension().x); x += PARTICLE_RADIUS / 2) {
        for (float z = _glass->origin().z; z < _uniformGrid.origin().z + _glass->dimension().z; z += PARTICLE_RADIUS / 2) {
            for (float y = _glass->origin().y; y < _uniformGrid.origin().y + _glass->dimension().y; y += PARTICLE_RADIUS / 2) {
                if (++_numberOfParticle >= MAX_PARTICLE) {
                    return;
                }
                Particle *p = new Particle(Vect3f(x, y, z));
                p->status = TO_UPDATE;
                _uniformGrid(0, 0, 0).push_back(p);
                _fluidBody.addParticle(p);
            }
        }
    }
}

void SphFluidDemo::update()
{
    static int i = 0;

    ++i;
    if (Timer::instance()->getElapsedTime("sph-fps") > 1000) {
        Timer::instance()->update("sph-fps");
        _currentFPS = i;
        i = 0;
    }
//    _tp.addTask(new Task(&executeStep, new std::string("step1")));
    step1();
    step2();
    float dt = 1.0 / 100.0;
    for (std::list<Particle *>::iterator it = _fluidBody.particles().begin(); it != _fluidBody.particles().end(); ++it) {
        Vect3f newPosition = (*it)->position + (*it)->velocity * dt + (*it)->acceleration * dt * dt;
        Vect3f newVelocity = (newPosition - (*it)->position) / dt;

        (*it)->position = newPosition;
        (*it)->velocity = newVelocity;
    }

    _uniformGrid.update();
}

// Update density and pressure for each particle
void SphFluidDemo::step1()
{
    for (std::list<Particle *>::iterator particle = _fluidBody.particles().begin(); particle != _fluidBody.particles().end(); ++particle) {
        float kernels = 0.0;
        int i = 0;

        _uniformGrid.getNeighborParticles(_neighbors, **particle);
        while (_neighbors[i]) {
            Vect3f diffPosition = (*particle)->position - _neighbors[i]->position;
            kernels += wpoly6Kernel(diffPosition.dot(diffPosition));
            ++i;
        }

        (*particle)->density = kernels * PARTICLE_MASS;
        (*particle)->pressure = WATER_STIFFNESS * ((*particle)->density - PARTICLE_DENSITY_REST); //pressure = k(ρ − ρ0)
    }
}

// Calculate external forces applied to each particles
// Interpretation of given sph formulas, see docs
void SphFluidDemo::step2()
{
    for (std::list<Particle *>::iterator particle = _fluidBody.particles().begin(); particle != _fluidBody.particles().end(); ++particle) {
        Vect3f f_pressure, f_viscosity, f_surface, colorField;
        Vect3f f_gravity(0, GRAVITY * (*particle)->density, 0);
        float colorFieldLaplacian = 0.0;
        int i = 0;

        _uniformGrid.getNeighborParticles(_neighbors, **particle);
        while (_neighbors[i]) {
            Vect3f distance = (*particle)->position - _neighbors[i]->position;
            double dotRadius = distance.dot(distance);

            if (dotRadius <= PARTICLE_RADIUS_SQUARE) {
                Vect3f poly6Gradient = wpoly6KernelGradient(dotRadius, distance);
                Vect3f spikyGradient = spikyKernelGradient(dotRadius, distance);
                if (_neighbors[i] != *particle) {
                    f_pressure += noSymmetricalPressure((*particle)->pressure, (*particle)->density, _neighbors[i]->pressure, _neighbors[i]->density, spikyGradient);
                    f_viscosity += noSymmetricalViscosity((*particle)->velocity, _neighbors[i]->velocity, _neighbors[i]->density, viscosityKernel(dotRadius));
                }
                colorField += poly6Gradient / _neighbors[i]->density * PARTICLE_MASS;
                colorFieldLaplacian += wpoly6KernelSecond(dotRadius) / _neighbors[i]->density * PARTICLE_MASS;
            }
            ++i;
        }

        (*particle)->normal = colorField * -1;
        float colorFieldNormalMagnitude = colorField.magnitude();
        if (colorFieldNormalMagnitude > SURFACE_THRESHOLD) {
            f_surface = -SURFACE_TENSION * colorField / colorFieldNormalMagnitude * colorFieldLaplacian;
        }
        (*particle)->acceleration = (f_pressure + f_viscosity + f_gravity) / (*particle)->density;
        (*particle)->acceleration += _glass->collision(**particle);
    }
}

void SphFluidDemo::draw()
{
    render.render(_fluidBody, *_glass);
}

int SphFluidDemo::numberOfParticle() const
{
    return _numberOfParticle;
}

int SphFluidDemo::fps() const
{
    return _currentFPS;
}

void executeStep(void *data)
{
    SphFluidDemo::instance()->step1();
}

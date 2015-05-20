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
surfaceThreshold(0.01),
camera(CAMERA_ANGLE, CAMERA_DISTANCE, 70),
grid(Vect3f(0, 0, 0), Vect3f(10, 10, 10))
{
    int numberOfParticle = 0;
    vector<Particle *>& firstGridCell = grid(0,0,0);
    for (float y = grid.origin().y; y < grid.origin().y + grid.boxSize.y; y += PARTICLE_RADIUS / 2.0) {
        for (float x = grid.origin().x; x < (grid.origin().x + grid.boxSize.x * 0.25); x += PARTICLE_RADIUS / 2.0) {
            for (float z = grid.origin().z; z < grid.origin().z + grid.boxSize.z; z += PARTICLE_RADIUS / 2.0) {
                Particle *p = new Particle(Vect3f(x, y,z), numberOfParticle);
                firstGridCell.push_back(p);
                fluidBody.addParticle(p);
                ++numberOfParticle;
            }
        }
    }
    camera.init(grid.center, Vect3f(0, 1, 0));
    updateGrid();
}

SphFluidDemo::~SphFluidDemo()
{
}

void SphFluidDemo::update()
{
    float dt = 1.0 / 100.0;
    pressureEngine();
    physicsEngine();
    for (unsigned int gridCellIndex = 0; gridCellIndex < grid.cellCount(); gridCellIndex++) {
        
        vector<Particle *>& particles = grid.data()[gridCellIndex];
        
        for (unsigned int p = 0; p < particles.size(); p++) {
            
            Particle * particle = particles[p];
            
            Vect3f newPosition = particle->position() + particle->velocity()*dt + particle->acceleration()*dt*dt;
            Vect3f newVelocity = (newPosition - particle->position()) / dt;
            
            particle->position() = newPosition;
            particle->velocity() = newVelocity;
        }
    }
    
    updateGrid();
}

// to update the grid cells particles are located in
// should be called right after particle positions are updated
void SphFluidDemo::updateGrid() {
    
    for (unsigned int x = 0; x < grid.dimension().x; x++) {
        for (unsigned int y = 0; y < grid.dimension().y; y++) {
            for (unsigned int z = 0; z < grid.dimension().z; z++) {
                vector<Particle *>& particles = grid(x,y,z);
                
                for (int p = 0; p < particles.size(); p++) {
                    Particle * particle = particles[p];
                    int newGridCellX = (int)floor((particle->position().x + 0.1) / PARTICLE_RADIUS);
                    int newGridCellY = (int)floor((particle->position().y + 0.1) / PARTICLE_RADIUS);
                    int newGridCellZ = (int)floor((particle->position().z + 0.1) / PARTICLE_RADIUS);

                    if (newGridCellX < 0)
                        newGridCellX = 0;
                    else if (newGridCellX >= grid.dimension().x)
                        newGridCellX = grid.dimension().x - 1;
                    if (newGridCellY < 0)
                        newGridCellY = 0;
                    else if (newGridCellY >= grid.dimension().y)
                        newGridCellY = grid.dimension().y - 1;
                    if (newGridCellZ < 0)
                        newGridCellZ = 0;
                    else if (newGridCellZ >= grid.dimension().z)
                        newGridCellZ = grid.dimension().z - 1;
                    
                    if (x != newGridCellX || y != newGridCellY || z != newGridCellZ) {
                        // move the particle to the new grid cell
                        grid(newGridCellX, newGridCellY, newGridCellZ).push_back(particle);
                        
                        // remove it from it's previous grid cell
                        particles[p] = particles.back();
                        particles.pop_back();
                        p--; // important! make sure to redo this index, since a new particle will (probably) be there
                    }
                }
            }
        }
    }
}

/*
 Calculate the acceleration of each particle using a grid optimized approach.
 For each particle, only particles in the same grid cell and the (26) neighbor->ing grid cells must be considered,
 since any particle beyond a grid cell distance away contributes no force.
 */
void SphFluidDemo::pressureEngine()
{
    for (int x = 0; x < grid.dimension().x; x++) {
        for (int y = 0; y < grid.dimension().y; y++) {
            for (int z = 0; z < grid.dimension().z; z++) {
                vector<Particle *>& particles = grid(x,y,z);
                for (int p = 0; p < particles.size(); p++) {
                    Particle * particle = particles[p];
                    float kernels = 0.0;
                    
                    for (int offsetX = -1; offsetX <= 1; offsetX++) {
                        if (x+offsetX < 0) continue;
                        if (x+offsetX >= grid.dimension().x) break;
                        
                        for (int offsetY = -1; offsetY <= 1; offsetY++) {
                            if (y+offsetY < 0) continue;
                            if (y+offsetY >= grid.dimension().y) break;
                            
                            for (int offsetZ = -1; offsetZ <= 1; offsetZ++) {
                                if (z+offsetZ < 0) continue;
                                if (z+offsetZ >= grid.dimension().z) break;
                                
                                vector<Particle *>& neighborGridCellParticles = grid(x+offsetX, y+offsetY, z+offsetZ);
                                
                                for (int i = 0; i < neighborGridCellParticles.size(); i++) {
                                    Particle * neighborParticle = neighborGridCellParticles[i];
                                    Vect3f diffPosition = particle->position() - neighborParticle->position();
                                    kernels += wpoly6Kernel(diffPosition.dot(diffPosition));
                                }
                            }
                        }
                    }
                    
                    particle->density() = kernels * PARTICLE_MASS;
                    particle->pressure() = WATER_STIFFNESS * (particle->density() - PARTILE_DENSITY_REST); //pressure = k(ρ − ρ0)
                }
            }
        }
    }
}

void SphFluidDemo::physicsEngine()
{
    for (int x = 0; x < grid.dimension().x; x++) {
        for (int y = 0; y < grid.dimension().y; y++) {
            for (int z = 0; z < grid.dimension().z; z++) {
                vector<Particle *>& particles = grid(x,y,z);
                for (int p = 0; p < particles.size(); p++) {
                    Particle * particle = particles[p];
                    Vect3f f_pressure,
                    f_viscosity,
                    f_surface,
                    colorField;
                    Vect3f f_gravity = Vect3f(0, GRAVITY, 0) * particle->density();
                    
                    double colorFieldLaplacian = 0.0;
                    
                    for (int offsetX = -1; offsetX <= 1; offsetX++) {
                        if (x+offsetX < 0) continue;
                        if (x+offsetX >= grid.dimension().x) break;
                        
                        for (int offsetY = -1; offsetY <= 1; offsetY++) {
                            if (y+offsetY < 0) continue;
                            if (y+offsetY >= grid.dimension().y) break;
                            
                            for (int offsetZ = -1; offsetZ <= 1; offsetZ++) {
                                if (z+offsetZ < 0) continue;
                                if (z+offsetZ >= grid.dimension().z) break;
                                
                                vector<Particle *>& neighborGridCellParticles = grid(x+offsetX, y+offsetY, z+offsetZ);
                                
                                for (int i = 0; i < neighborGridCellParticles.size(); i++) {
                                    Particle * neighbor = neighborGridCellParticles[i];
                                    Vect3f diffPosition = particle->position() - neighbor->position();
                                    double radiusSquared = diffPosition.dot(diffPosition);
                                    
                                    if (radiusSquared <= PARTICLE_RADIUS * PARTICLE_RADIUS) {
                                        Vect3f poly6Gradient = wpoly6KernelGradient(radiusSquared, diffPosition);
                                        Vect3f spikyGradient = spikyKernelGradient(radiusSquared, diffPosition);
                                        
                                        if (particle->id() != neighbor->id()) {
                                            f_pressure += noSymmetricalPressure(particle->pressure(), particle->density(), neighbor->pressure(), neighbor->density(), spikyGradient);
                                            f_viscosity += noSymmetricalViscosity(particle->velocity(), neighbor->velocity(), neighbor->density(), viscosityKernel(radiusSquared));
                                        }
                                        colorField += PARTICLE_MASS * poly6Gradient / neighbor->density();
                                        colorFieldLaplacian +=  PARTICLE_MASS * wpoly6KernelSecond(radiusSquared) / neighbor->density();
                                    }
                                }
                            }
                        }
                    }
                    particle->normal = -1.0 * colorField;
                    
                    // surface tension force
                    double colorFieldNormalMagnitude = colorField.magnitude();
                    if (colorFieldNormalMagnitude > SURFACE_THRESHOLD) {
                        f_surface = -SURFACE_TENSION * colorField / colorFieldNormalMagnitude * colorFieldLaplacian;
                    }
                    
                    
                    particle->acceleration() = (f_pressure + f_viscosity + f_surface + f_gravity) / particle->density();
                    
                    // EXTERNAL FORCES HERE (USER INTERACTION, SWIRL)
                    Vect3f f_collision;
                    collisionForce(particle);
                }
            }
        }
    }
}

void SphFluidDemo::collisionForce(Particle * particle) {
    std::list<Wall> walls = grid.getWalls();
    for (std::list<Wall>::iterator it = walls.begin(); it != walls.end(); ++it) {
        Vect3f center = (*it).center();
        Vect3f normal = (*it).normal();
        double d = (center - particle->position()).dot(normal) + 0.01; // particle radius
        
        if (d > 0.0) {
            particle->acceleration() += WALL_RESISTANCE * normal * d;
            particle->acceleration() += WALL_DAMPING * particle->velocity().dot(normal) * normal;
        }
    }
}

void SphFluidDemo::draw()
{
    static Vect3f blackColor(0,0,0);
    static Vect3f blueColor(0,0,1);
    static Vect3f whiteColor(1,1,1);
    static Vect3f greyColor(0.2, 0.2, 0.2);
    static Vect3f lightGreyColor(0.8,0.8,0.8);

    glEnable(GL_LIGHTING);
    
    for (int gridCellIndex = 0; gridCellIndex < grid.cellCount(); gridCellIndex++) {
        vector<Particle *>& particles = grid.data()[gridCellIndex];
        for (int p = 0; p < particles.size(); p++) {
            Particle * particle = particles[p];
            particle->draw();
        }
    }
    glDisable(GL_LIGHTING);
    
    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(grid.center.x, grid.center.y, grid.center.z);
    glScaled(grid.boxSize.x, grid.boxSize.y, grid.boxSize.z);
    glutWireCube(1.0);
    glPopMatrix();
}

//#include <GLUT/GLUT.h>
//#include <iostream>
//
//#include "SphFluidDemo.h"
//#include "config.h"
//#include "sph_formulas.h"
//
//SphFluidDemo::SphFluidDemo() :
//grid(Vect3f(0, 0, 0), Vect3f(GRID_SIZE, GRID_SIZE, GRID_SIZE)),
//camera(1.5, 20, 70)
//{
//    std::cout << "demo started" << std::endl;
//}
//
//SphFluidDemo::~SphFluidDemo()
//{
//    std::cout << "demo finished" << std::endl;
//}
//
//void SphFluidDemo::init()
//{
//    renderer.init();
//    Vect3f eye = grid.getCenter() * 0.5;
//    camera.init(eye, grid.getCenter(), Vect3f(0, 1, 0));
//
//    int numberOfParticle = 0;
//    for (float x = 0; x < grid.dimension().x; x += 2 * PARTICLE_RADIUS) {
//        for (float z = 0; z < grid.dimension().z; z += 2 * PARTICLE_RADIUS) {
//            for (float y = 0; y < grid.dimension().y; y += 2 * PARTICLE_RADIUS) {
//                if (++numberOfParticle > MAX_PARTICLE) {
//                    break;
//                }
//                Particle *p = new Particle(Vect3f(x, y, z));
//                fluidBody.addParticle(p);
//                grid(0, 0, 0).push_back(p);
//            }
//        }
//    }
//    grid.update();
//}
//
//void SphFluidDemo::update()
//{
//    step1();
//    step2();
//
//    float dt = 1.0 / 100.0;
//    std::list<Particle *> particles = fluidBody.getParticles();
//    for (std::list<Particle *>::iterator it = particles.begin(); it != particles.end(); ++it) {
//        Vect3f position = (*it)->position;
//        Vect3f velocity = (*it)->velocity * dt;
//        Vect3f acceleration = (*it)->acceleration * dt * dt;
//        Vect3f newPosition = position + velocity + acceleration;
//        Vect3f newVelocity = (newPosition - (*it)->position) / dt;;
//
//        (*it)->position = newPosition;
//        (*it)->velocity = newVelocity;
//    }
//
//    grid.update();
//}
//
//// update density and pressure for each particle
//void SphFluidDemo::step1()
//{
//    std::list<Particle *> particles = fluidBody.getParticles();
//    for (std::list<Particle *>::iterator particle = particles.begin(); particle != particles.end(); ++particle) {
//        float kernels = 0.0;
//        std::list<Particle *> * neightborParticles = grid.getneighbor->Particles(**particle);
//        for (std::list<Particle *>::iterator it = neightborParticles->begin(); it != neightborParticles->end(); ++it) {
//            Vect3f distance = (*particle)->position - (*it)->position;
//            kernels += wpoly6Kernel(distance.dot(distance));
//        }
//        (*particle)->density = kernels * PARTICLE_MASS;
//        (*particle)->pressure = WATER_STIFFNESS * ((*particle)->density - PARTICLE_DENSITY_REST); //pressure = k(ρ − ρ0);
//        neightborParticles->clear();
//        delete neightborParticles;
//    }
//}
//
//
//void SphFluidDemo::step2()
//{
//    std::list<Particle *> particles = fluidBody.getParticles();
//    for (std::list<Particle *>::iterator particle = particles.begin(); particle != particles.end(); ++particle) {
//        std::list<Particle *> * neightborParticles = grid.getneighbor->Particles(**particle);
//        Vect3f f_pressure, f_viscosity, f_surface, colorField;
//        Vect3f f_gravity(0, GRAVITY, 0);
//        float colorFieldLaplacian = 0.0;
//        
//        for (std::list<Particle *>::iterator it = neightborParticles->begin(); it != neightborParticles->end(); ++it) {
//            Vect3f distance = (*particle)->position - (*it)->position;
//            float dotRadius = distance.dot(distance);
//            if (dotRadius < PARTICLE_RADIUS_SQUARE) {
//                Vect3f poly6Gradient = wpoly6KernelGradient(dotRadius, distance);
//                Vect3f spikyGradient = spikyKernelGradient(dotRadius, distance);
//                if (*it != *particle) {
//                    f_pressure += noSymmetricalPressure((*particle)->pressure, (*particle)->density, (*it)->pressure, (*it)->density, spikyGradient);
//                    f_viscosity += noSymmetricalViscosity((*particle)->velocity, (*it)->velocity, (*it)->density, viscosityKernel(dotRadius));
//                }
//                colorField += poly6Gradient / (*it)->density * PARTICLE_MASS;
//                colorFieldLaplacian += wpoly6KernelSecond(dotRadius) / (*it)->density * PARTICLE_MASS;
//            }
//        }
//        
//        (*particle)->normal = colorField * -1;
//        float colorFieldNormalMagnitude = colorField.magnitude();
//        if (colorFieldNormalMagnitude > SURFACE_THRESHOLD) {
//            f_surface = colorField / colorFieldNormalMagnitude * colorFieldLaplacian * -SURFACE_TENSION;
//        }
//        (*particle)->acceleration = (f_pressure + f_viscosity + f_surface + f_gravity) / (*particle)->density;
//        collisions(**particle);
//
//        neightborParticles->clear();
//        delete neightborParticles;
//    }
//}
//
//void SphFluidDemo::collisions(Particle & particle)
//{
//    std::list<Wall *> walls = grid.getWalls();
//
//    for (std::list<Wall *>::iterator it = walls.begin(); it != walls.end(); ++it) {
//        Vect3f center = (*it)->center;
//        Vect3f normal = (*it)->normal;
//        float d = (center - particle->position).dot(normal) + 0.01;
//        if (d > 0.0) {
//            particle->acceleration += normal * WALL_RESISTANCE * d;
//            particle->acceleration += normal * particle->velocity.dot(normal) * WALL_DAMPING;
//        }
//    }
//}
//
//void SphFluidDemo::display()
//{
//    renderer.render();
//}

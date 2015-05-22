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
    glass = new Glass(Vect3f(0, 0, 0), Vect3f(0.4, 0.4, 0.4));
    camera.init(glass->center(), Vect3f(0, 1, 0));

    int numberOfParticle = 0;
    for (float x = glass->origin().x; x < (glass->origin().x + glass->dimension().x); x += PARTICLE_RADIUS / 2) {
        for (float z = glass->origin().z; z < uniformGrid.origin().z + glass->dimension().z; z += PARTICLE_RADIUS / 2) {
            for (float y = glass->origin().y; y < uniformGrid.origin().y + glass->dimension().y; y += PARTICLE_RADIUS / 2) {
                if (numberOfParticle > MAX_PARTICLE) {
                    break;
                }
                Particle *p = new Particle(Vect3f(x, y, z), numberOfParticle);
                uniformGrid(0, 0, 0).push_back(p);
                fluidBody.addParticle(p);
                ++numberOfParticle;
            }
        }
    }

    uniformGrid.update();
}

SphFluidDemo::~SphFluidDemo()
{}

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
// update density and pressure for each particle
void SphFluidDemo::step1()
{
//    for (std::list<Particle *>::iterator particle = fluidBody.particles().begin(); particle != fluidBody.particles().end(); ++particle) {
//        float kernels = 0.0;
//        std::vector<Particle *> *neighborParticles = grid.getNeighborParticles(**particle);
//        for (std::vector<Particle *>::iterator it = neighborParticles->begin(); it != neighborParticles->end(); ++it) {
//            Vect3f distance = (*particle)->position - (*it)->position;
//            kernels += wpoly6Kernel(distance.dot(distance));
//        }
//        (*particle)->density = kernels * PARTICLE_MASS;
//        (*particle)->pressure = WATER_STIFFNESS * ((*particle)->density - PARTICLE_DENSITY_REST); //pressure = k(ρ − ρ0);
//        neighborParticles->clear();
//        delete neighborParticles;
//    }
    for (int x = 0; x < uniformGrid.dimension().x; x++) {
        for (int y = 0; y < uniformGrid.dimension().y; y++) {
            for (int z = 0; z < uniformGrid.dimension().z; z++) {
                std::vector<Particle *>& particles = uniformGrid(x,y,z);
                for (int p = 0; p < particles.size(); p++) {
                    Particle * particle = particles[p];
                    float kernels = 0.0;
                    
                    for (int offsetX = -1; offsetX <= 1; offsetX++) {
                        if (x+offsetX < 0) continue;
                        if (x+offsetX >= uniformGrid.dimension().x) break;
                        
                        for (int offsetY = -1; offsetY <= 1; offsetY++) {
                            if (y+offsetY < 0) continue;
                            if (y+offsetY >= uniformGrid.dimension().y) break;
                            
                            for (int offsetZ = -1; offsetZ <= 1; offsetZ++) {
                                if (z+offsetZ < 0) continue;
                                if (z+offsetZ >= uniformGrid.dimension().z) break;
                                
                                std::vector<Particle *>& neighborGridCellParticles = uniformGrid(x+offsetX, y+offsetY, z+offsetZ);
                                
                                for (int i = 0; i < neighborGridCellParticles.size(); i++) {
                                    Particle * neighborParticle = neighborGridCellParticles[i];
                                    Vect3f diffPosition = particle->position - neighborParticle->position;
                                    kernels += wpoly6Kernel(diffPosition.dot(diffPosition));
                                }
                            }
                        }
                    }
                    
                    particle->density = kernels * PARTICLE_MASS;
                    particle->pressure = WATER_STIFFNESS * (particle->density - PARTICLE_DENSITY_REST); //pressure = k(ρ − ρ0)
                }
            }
        }
    }
}

void SphFluidDemo::step2()
{
    for (int x = 0; x < uniformGrid.dimension().x; x++) {
        for (int y = 0; y < uniformGrid.dimension().y; y++) {
            for (int z = 0; z < uniformGrid.dimension().z; z++) {
                std::vector<Particle *>& particles = uniformGrid(x,y,z);
                for (int p = 0; p < particles.size(); p++) {
                    Particle * particle = particles[p];
                    Vect3f f_pressure,
                    f_viscosity,
                    f_surface,
                    colorField;
                    Vect3f f_gravity = Vect3f(0, GRAVITY, 0) * particle->density;
                    
                    double colorFieldLaplacian = 0.0;
                    
                    for (int offsetX = -1; offsetX <= 1; offsetX++) {
                        if (x+offsetX < 0) continue;
                        if (x+offsetX >= uniformGrid.dimension().x) break;
                        
                        for (int offsetY = -1; offsetY <= 1; offsetY++) {
                            if (y+offsetY < 0) continue;
                            if (y+offsetY >= uniformGrid.dimension().y) break;
                            
                            for (int offsetZ = -1; offsetZ <= 1; offsetZ++) {
                                if (z+offsetZ < 0) continue;
                                if (z+offsetZ >= uniformGrid.dimension().z) break;
                                
                                std::vector<Particle *>& neighborGridCellParticles = uniformGrid(x+offsetX, y+offsetY, z+offsetZ);
                                
                                for (int i = 0; i < neighborGridCellParticles.size(); i++) {
                                    Particle * neighbor = neighborGridCellParticles[i];
                                    Vect3f diffPosition = particle->position - neighbor->position;
                                    double radiusSquared = diffPosition.dot(diffPosition);
                                    
                                    if (radiusSquared <= PARTICLE_RADIUS * PARTICLE_RADIUS) {
                                        Vect3f poly6Gradient = wpoly6KernelGradient(radiusSquared, diffPosition);
                                        Vect3f spikyGradient = spikyKernelGradient(radiusSquared, diffPosition);
                                        
                                        if (particle->id() != neighbor->id()) {
                                            f_pressure += noSymmetricalPressure(particle->pressure, particle->density, neighbor->pressure, neighbor->density, spikyGradient);
                                            f_viscosity += noSymmetricalViscosity(particle->velocity, neighbor->velocity, neighbor->density, viscosityKernel(radiusSquared));
                                        }
                                        colorField += PARTICLE_MASS * poly6Gradient / neighbor->density;
                                        colorFieldLaplacian +=  PARTICLE_MASS * wpoly6KernelSecond(radiusSquared) / neighbor->density;
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
                    
                    
                    particle->acceleration = (f_pressure + f_viscosity + f_surface + f_gravity) / particle->density;
                    
                    // EXTERNAL FORCES HERE (USER INTERACTION, SWIRL)
                    Vect3f f_collision;
                    collisions(particle);
                }
            }
        }
    }
}

void SphFluidDemo::collisions(Particle * particle) {
    std::list<Wall> walls = glass->getWalls();
    for (std::list<Wall>::iterator it = walls.begin(); it != walls.end(); ++it) {
        Vect3f center = (*it).center();
        Vect3f normal = (*it).normal();
        double d = (center - particle->position).dot(normal) + 0.01; // particle radius
        
        if (d > 0.0) {
            particle->acceleration += WALL_RESISTANCE * normal * d;
            particle->acceleration += WALL_DAMPING * particle->velocity.dot(normal) * normal;
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
    
    for (int gridCellIndex = 0; gridCellIndex < uniformGrid.numberOfCell(); gridCellIndex++) {
        std::vector<Particle *>& particles = uniformGrid.particles()[gridCellIndex];
        for (int p = 0; p < particles.size(); p++) {
            Particle * particle = particles[p];
            particle->draw();
        }
    }
    glDisable(GL_LIGHTING);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(glass->center().x, glass->center().y, glass->center().z);
    glScaled(glass->dimension().x, glass->dimension().y, glass->dimension().z);
    glutWireCube(1.0);
    glPopMatrix();
}

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

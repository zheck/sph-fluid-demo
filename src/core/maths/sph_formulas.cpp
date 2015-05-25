//
//  sph_formulas.cpp
//  sph-fluid
//
//  Created by zhou on 5/16/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include <math.h>

#include "sph_formulas.h"
#include "config.h"

float wpoly6Kernel(float positionSquare)
{
    static const float coeff = 315.0 / (64.0 * M_PI * pow(PARTICLE_RADIUS, 9));
    if (positionSquare > PARTICLE_RADIUS_SQUARE)
        return 0;

    return coeff * pow(PARTICLE_RADIUS_SQUARE - positionSquare, 3);
}

Vect3f wpoly6KernelGradient(float positionSquare, Vect3f const & spaceDiff)
{
    static const float coeff = -945.0 / (32.0 * M_PI * pow(PARTICLE_RADIUS, 9));

    return spaceDiff * coeff * pow(PARTICLE_RADIUS_SQUARE - positionSquare, 2);
}

float wpoly6KernelSecond(float positionSquare)
{
    static const float coefficient = -945.0 / (32.0 * M_PI * pow(PARTICLE_RADIUS, 9));

    return coefficient * (PARTICLE_RADIUS_SQUARE - positionSquare) * (3.0 * PARTICLE_RADIUS_SQUARE - 7.0 * positionSquare);
}

Vect3f spikyKernelGradient(float positionSquare, Vect3f const & spaceDiff)
{
    static const float coeff = -45.0 / (M_PI * pow(PARTICLE_RADIUS, 6));
    float radius = sqrt(positionSquare);

    return (spaceDiff / PARTICLE_RADIUS) * coeff * pow(PARTICLE_RADIUS - radius, 2);
}

float viscosityKernel(float positionSquare)
{
    static const float coeff = 45.0 / (M_PI * pow(PARTICLE_RADIUS, 6));
    double radius = sqrt(positionSquare);

    return coeff * (PARTICLE_RADIUS - radius);
}

Vect3f noSymmetricalViscosity(Vect3f const & velocity,
                             Vect3f const & neighborVelocity,
                             float neighborDensity,
                             float viscosityKernel)
{
    static const float coeff = PARTICLE_VISCOSITY * PARTICLE_MASS;

    return (neighborVelocity - velocity) * coeff * viscosityKernel / neighborDensity;
}

Vect3f noSymmetricalPressure(float particlePressure,
                            float particleDensity,
                            float neighborPressure,
                            float neighborDensity,
                            Vect3f const & spikyGradient)
{
    Vect3f coeff = spikyGradient * -particleDensity * PARTICLE_MASS;

    return coeff * (particlePressure / pow(particleDensity, 2) + (neighborPressure / pow(neighborDensity, 2)));
}

//
//  Particle.h
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Particle__
#define __sph_fluid__Particle__

#include <stdio.h>
#include <iostream>

#include "Vect3f.h"

class Particle
{
public:
    Vect3f position;
    Vect3f velocity;
    Vect3f normal;
    Vect3f acceleration;
    float density;
    float pressure;

public:
    Particle(Vect3f const & position);
    Particle(Particle const & rhs);
    ~Particle();

    Particle & operator=(Particle const & rhs);
};

#endif /* defined(__sph_fluid__Particle__) */

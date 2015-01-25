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
    Vect3f _position;

public:
    Particle(Vect3f const & position);
    Particle(Particle const & rhs);
    ~Particle();

    Particle & operator=(Particle const & rhs);

    Vect3f & getPosition();
};

#endif /* defined(__sph_fluid__Particle__) */

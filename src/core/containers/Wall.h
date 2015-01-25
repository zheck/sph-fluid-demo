//
//  Wall.h
//  sph-fluid
//
//  Created by zhou on 2/3/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Wall__
#define __sph_fluid__Wall__

#include <stdio.h>

#include "Vect3f.h"

class Wall
{
public:
    Vect3f center;
    Vect3f normal;
    float size;
    float thickness;

public:
    Wall(Vect3f const & origin, Vect3f const & center);
    Wall(Wall const & rhs);
    ~Wall();

    Wall & operator=(Wall const & rhs);
};

#endif /* defined(__sph_fluid__Wall__) */

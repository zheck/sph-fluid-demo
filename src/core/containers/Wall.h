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
    Vect3f _center;
    Vect3f _normal;
    float _size;
    
public:
    Wall(Vect3f const & center, Vect3f const & normal);
    Wall(Wall const & rhs);
    ~Wall();
    
    Wall & operator=(Wall const & rhs);
    
    Vect3f & normal();
    Vect3f & center();
    
    void draw();
};

#endif /* defined(__sph_fluid__Wall__) */

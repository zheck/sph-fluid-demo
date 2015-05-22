//
//  Glass.h
//  sph-fluid
//
//  Created by zhou on 5/21/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Glass__
#define __sph_fluid__Glass__

#include <stdio.h>
#include <list>

#include "Vect3f.h"
#include "Wall.h"

class Glass
{
    Vect3f _origin;
    Vect3f _dimension;
    Vect3f _center;
    std::list<Wall> _walls;

public:
    Glass(Vect3f const & origin, Vect3f const & dimension);
    Glass(Glass const & rhs);
    ~Glass();

    Glass & operator=(Glass const & rhs);

    Vect3f origin() const;
    Vect3f center() const;
    Vect3f dimension() const;
    std::list<Wall> & getWalls();
};

#endif /* defined(__sph_fluid__Glass__) */

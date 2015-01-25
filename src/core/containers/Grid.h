//
//  Grid.h
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Grid__
#define __sph_fluid__Grid__

#include <stdio.h>
#include <math.h>
#include <list>
#include <vector>

#include "Vect3f.h"
#include "Wall.h"
#include "Particle.h"

class Grid
{
protected:
    Vect3f _origin;
    Vect3f _dimension;
    std::list<Wall *> _walls;
    std::vector<Particle *> *_particles;
    int _numberOfCell;

public:
    Grid(Vect3f const & origin, Vect3f const & dimension);
    Grid(Grid const & rhs);
    ~Grid();

    Grid & operator=(Grid const & rhs);
    std::vector<Particle *> & operator()(int x, int y, int z);

    std::list<Wall *> & getWalls();
    Vect3f & origin();
    Vect3f & dimension();
    Vect3f getCenter() const;
    void update();

private:
    int getNextPowerOf2(int number);
};

#endif /* defined(__sph_fluid__Grid__) */

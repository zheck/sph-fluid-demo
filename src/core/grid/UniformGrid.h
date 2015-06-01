//
//  UniformGrid.h
//  sph-fluid
//
//  Created by zhou on 5/21/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__UniformGrid__
#define __sph_fluid__UniformGrid__

#include <stdio.h>
#include <list>

#include "Vect3f.h"
#include "Particle.h"

class UniformGrid
{
    Vect3f _origin;
    Vect3f _dimension;
    std::list<Particle *> * _particles;
    int _numberOfCell;

public:
    UniformGrid(Vect3f const & origin, Vect3f const & dimension);
    UniformGrid(UniformGrid const & rhs);
    ~UniformGrid();

    UniformGrid & operator=(UniformGrid const & rhs);
    std::list<Particle *> & operator()(int x, int y, int z);
    std::list<Particle *> & operator()(int position);

    Vect3f origin() const;
    Vect3f dimension() const;
    int numberOfCell() const;
    void update();
    int particleCellId(Vect3f & position) const;
    void getNeighborParticles(std::vector<Particle *> & neighbors, Particle & particle);

protected:
    // return grid axe position for given value, return value is inside min and max range
    int positionInsideGrid(float value, int min, int max) const;
};

#endif /* defined(__sph_fluid__UniformGrid__) */

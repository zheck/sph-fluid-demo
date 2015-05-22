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
#include <vector>

#include "Vect3f.h"
#include "Particle.h"

class UniformGrid
{
    Vect3f _origin;
    Vect3f _dimension;
    std::vector<Particle *> * _particles;
    int _numberOfCell;

public:
    UniformGrid(Vect3f const & origin, Vect3f const & dimension);
    UniformGrid(UniformGrid const & rhs);
    ~UniformGrid();

    UniformGrid & operator=(UniformGrid const & rhs);
    std::vector<Particle *> & operator()(int x, int y, int z);

    Vect3f origin() const;
    Vect3f dimension() const;
    int numberOfCell() const;
    void update();
    std::vector<Particle *> * getNeighborParticles(Particle & particle);
    std::vector<Particle *> * particles() {return _particles;};

protected:
    void addParticleForCellId(std::vector<Particle *> &particles, int posx, int posy, int posz);
    int newPosition(float value, int min, int max) const;
};

#endif /* defined(__sph_fluid__UniformGrid__) */
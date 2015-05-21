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
#include <vector>
#include <list>

#include "Vect3f.h"
#include "Wall.h"
#include "Particle.h"

class Grid
{
    Vect3f _origin;
    Vect3f _dimension;
    Vect3f _center;
    std::list<Wall> _walls;
    std::vector<Particle *> *_particles;
    int _numberOfCell;

public:
    Vect3f boxSize;

public:
    Grid(Vect3f const & origin, Vect3f const & dimension);
    Grid(Grid const & rhs);
    ~Grid();

    Grid & operator=(Grid const & rhs);

    Vect3f origin() const;
    Vect3f center() const;
    Vect3f dimension() const;
    int numberOfCell() const;
    void update();
    std::list<Wall> & getWalls();
    std::vector<Particle *> & operator()(int x, int y, int z);
    std::vector<Particle *> * getNeighborParticles(Particle & particle);
    std::vector<Particle *> * particles() {return _particles;};
    
protected:
    void addParticleForCellId(std::vector<Particle *> &particles, int posx, int posy, int posz);
    int newPosition(float value, int min, int max) const;
};

#endif /* defined(__sph_fluid__Grid__) */

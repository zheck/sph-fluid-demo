//
//  UniformGrid.cpp
//  sph-fluid
//
//  Created by zhou on 5/21/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "config.h"
#include "UniformGrid.h"

UniformGrid::UniformGrid(Vect3f const & origin, Vect3f const & dimension) :
_origin(origin),
_dimension(dimension)
{
    _numberOfCell = _dimension.x * _dimension.y * _dimension.z;
    _particles = new std::vector<Particle *>[_numberOfCell];
}

UniformGrid::~UniformGrid()
{
    for (int i = 0; i < _numberOfCell; ++i) {
        _particles[i].clear();
    }
}

Vect3f UniformGrid::origin() const
{
    return _origin;
}

Vect3f UniformGrid::dimension() const
{
    return _dimension;
}

int UniformGrid::numberOfCell() const
{
    return _numberOfCell;
}

std::vector<Particle *> & UniformGrid::operator()(int x, int y, int z)
{
    return _particles[x + y * (int)_dimension.x + z * (int)_dimension.x * (int)_dimension.y];
}

void UniformGrid::update()
{
    for (int i = 0; i < _numberOfCell; ++i) {
        for (std::vector<Particle *>::iterator it = _particles[i].begin(); it != _particles[i].end(); ++it) {
            Vect3f position = (*it)->position;
            int newGridCellX = newPosition((*it)->position.x, 0, _dimension.x);
            int newGridCellY = newPosition((*it)->position.y, 0, _dimension.y);
            int newGridCellZ = newPosition((*it)->position.z, 0, _dimension.z);
            int positionId = newGridCellX + newGridCellY * GRID_SIZE + newGridCellZ * (GRID_SIZE * GRID_SIZE);

            if (i != positionId) {
                _particles[positionId].push_back(*it);
                _particles[i].erase(it);
                --it;
            }
        }
    }
}

std::list<Particle *> * UniformGrid::getNeighborParticles(Particle & particle)
{
    std::list<Particle *> *neighbors = new std::list<Particle *>();
    int posx = particle.position.x / PARTICLE_RADIUS;
    int posy = particle.position.y / PARTICLE_RADIUS;
    int posz = particle.position.z / PARTICLE_RADIUS;

    for (int i = -1; i <= 1; i++) {
        if (posx+i < 0 || posx+i >= _dimension.x)
            continue;

        for (int j = -1; j <= 1; j++) {
            if (posy+j < 0 || posy+j >= _dimension.y)
                continue;

            for (int k = -1; k <= 1; k++) {
                if (posz+k < 0 || posz+k >= _dimension.z)
                    continue;

                std::vector<Particle *>& neighborParticles = this->operator()(posx+i, posy+j, posz+k);
                for (std::vector<Particle *>::iterator it = neighborParticles.begin(); it != neighborParticles.end(); ++it) {
                    neighbors->push_back(*it);
                }
            }
        }
    }

    return neighbors;
}

int UniformGrid::newPosition(float value, int min, int max) const
{
    int res = (int)floor(value / PARTICLE_RADIUS);
    if (res < min) {
        res = min;
    }
    if (res >= max) {
        res = max - 1;
    }

    return res;
}

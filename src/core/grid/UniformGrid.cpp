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
    _particles = new std::list<Particle *>[_numberOfCell];
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

std::list<Particle *> & UniformGrid::operator()(int x, int y, int z)
{
    return _particles[x + y * (int)_dimension.x + z * (int)_dimension.x * (int)_dimension.y];
}

std::list<Particle *> & UniformGrid::operator()(int position)
{
    return _particles[position];
}

void UniformGrid::update()
{
    for (int i = 0; i < _numberOfCell; ++i) {
        for (std::list<Particle *>::iterator it = _particles[i].begin(); it != _particles[i].end(); ++it) {
            int positionId = particleCellId((*it)->position);

            if (i != positionId) {
                _particles[positionId].push_back(*it);
                _particles[i].erase(it);
                --it;
            }
        }
    }
}

int UniformGrid::particleCellId(Vect3f & position) const
{
    int posx = positionInsideGrid(position.x, 0, _dimension.x);
    int posy = positionInsideGrid(position.y, 0, _dimension.y);
    int posz = positionInsideGrid(position.z, 0, _dimension.z);

    return posx + posy * (int)_dimension.x + posz * (int)_dimension.x * (int)_dimension.y;
}

void UniformGrid::getNeighborParticles(std::vector<Particle *> &neighbors, Particle &particle)
{
    int posx = particle.position.x / PARTICLE_RADIUS;
    int posy = particle.position.y / PARTICLE_RADIUS;
    int posz = particle.position.z / PARTICLE_RADIUS;

    int numberOfParticle = 0;
    for (int i = -1; i <= 1; i++) {
        if (posx+i < 0 || posx+i >= _dimension.x)
            continue;

        for (int j = -1; j <= 1; j++) {
            if (posy+j < 0 || posy+j >= _dimension.y)
                continue;

            for (int k = -1; k <= 1; k++) {
                if (posz+k < 0 || posz+k >= _dimension.z)
                    continue;

                std::list<Particle *>& neighborParticles = this->operator()(posx+i, posy+j, posz+k);
                for (std::list<Particle *>::iterator it = neighborParticles.begin(); it != neighborParticles.end(); ++it) {
                    neighbors[numberOfParticle++] = *it;
                }
            }
        }
    }
    neighbors[numberOfParticle] = NULL;
}

int UniformGrid::positionInsideGrid(float value, int min, int max) const
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

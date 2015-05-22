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

std::vector<Particle *> * UniformGrid::getNeighborParticles(Particle & particle)
{
    std::vector<Particle *> *neighbors = new std::vector<Particle *>();
    int posx = (int)floor(particle.position.x / PARTICLE_RADIUS);
    int posy = (int)floor(particle.position.y / PARTICLE_RADIUS);
    int posz = (int)floor(particle.position.z / PARTICLE_RADIUS);

    for (int i = -1; i <= 1; ++i) {
        if (posx + i < 0 || posx + i > GRID_SIZE)
            continue;

        for (int j = -1; j <= 1; ++j) {
            if (posy + j < 0 || posy + j > GRID_SIZE)
                continue;

            for (int k = -1; k <= 1; ++k) {
                if (posz + k < 0 || posz + k > GRID_SIZE)
                    continue;
                addParticleForCellId(*neighbors, posx + i, posy + j, (posz + k));
            }
        }
    }

    return neighbors;
}

void UniformGrid::addParticleForCellId(std::vector<Particle *> &particles, int posx, int posy, int posz)
{
    int cellId = posx + posy * GRID_SIZE + posz * GRID_SIZE * GRID_SIZE;
    if (cellId < 0 || cellId > GRID_SIZE) {
        return ;
    }
    for (std::vector<Particle *>::iterator it = _particles[cellId].begin(); it != _particles[cellId].end(); ++it) {
        particles.push_back(*it);
    }
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
//std::list<Particle *> * Grid::getNeighborParticles(Particle & particle)
//{
//    std::list<Particle *> *neighbors = new std::list<Particle *>();
//    Vect3f position = particle.position;
//    int posx = (int)position.x;
//    int posy = (int)position.y;
//    int posz = (int)position.z;
//
//    for (int i = -1; i <= 1; ++i) {
//        if (posx + i < 0 || posx + i > GRID_SIZE)
//            continue;
//
//        for (int j = -1; j <= 1; ++j) {
//            if (posy + j < 0 || posy + j > GRID_SIZE)
//                continue;
//
//            for (int k = -1; k <= 1; ++k) {
//                if (posz + k < 0 || posz + k > GRID_SIZE)
//                    continue;
//                addParticleForCellId(*neighbors, posx + i + (posy + j) * GRID_SIZE + (posz + k) * GRID_SIZE * GRID_SIZE);
//            }
//        }
//    }
//
//    return neighbors;
//}
//
//void Grid::addParticleForCellId(std::list<Particle *> &particles, int cellId)
//{
//    if (cellId < 0 || cellId > GRID_SIZE) {
//        return ;
//    }
//    for (std::list<Particle *>::iterator it = _particles[cellId].begin(); it != _particles[cellId].end(); ++it) {
//        particles.push_back(*it);
//    }
//}

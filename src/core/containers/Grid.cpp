//
//  Grid.cpp
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include <algorithm>

#include "Grid.h"
#include "config.h"

Grid::Grid(Vect3f const & origin, Vect3f const & dimension) :
_origin(origin),
_dimension(dimension)
{
    Vect3f center = (_dimension - _origin) * 0.5;

    _walls.push_back(new Wall(Vect3f(center.x, _dimension.y, center.z), Vect3f(0, 1, 0))); // top
    _walls.push_back(new Wall(Vect3f(center.x, _origin.y, center.z), Vect3f(0, 1, 0))); // bot
    _walls.push_back(new Wall(Vect3f(_origin.x, center.y, center.z), Vect3f(1, 0, 0))); // left
    _walls.push_back(new Wall(Vect3f(_dimension.x, center.y, center.z), Vect3f(1, 0, 0))); // right
    _walls.push_back(new Wall(Vect3f(center.x, center.y, _origin.z), Vect3f(0, 0, 1))); // front
    _walls.push_back(new Wall(Vect3f(center.x, center.y, _dimension.z), Vect3f(0, 0, 1))); // back

    _numberOfCell = GRID_SIZE * GRID_SIZE * GRID_SIZE;
    _particles = new std::vector<Particle *>[_numberOfCell];
}

Grid::~Grid()
{
    for (std::list<Wall *>::iterator it = _walls.begin(); it != _walls.end(); ++it) {
        delete *it;
    }
    _walls.clear();
}

std::list<Wall *> & Grid::getWalls()
{
    return _walls;
}

std::vector<Particle *> & Grid::operator()(int x, int y, int z)
{
    return _particles[x + y * GRID_SIZE + z * GRID_SIZE * GRID_SIZE];
}

void Grid::update()
{
    for (int i = 0; i < _numberOfCell; ++i) {
        for (std::vector<Particle *>::iterator it = _particles[i].begin(); it != _particles[i].end(); ++it) {
            Vect3f position = (*it)->getPosition();
            int positionId = (int)position.x + (int)position.y * GRID_SIZE + (int)position.z * (GRID_SIZE * GRID_SIZE);
            if (positionId != i) {
                _particles[positionId].push_back(*it);
                _particles[i].erase(it);
                --it;
            }
        }
    }
}

Vect3f & Grid::origin()
{
    return _origin;
}

Vect3f & Grid::dimension()
{
    return _dimension;
}

Vect3f Grid::getCenter() const
{
    return (_dimension - _origin) * 0.5;
}

int Grid::getNextPowerOf2(int number)
{
    unsigned int power = 0;

    --number;
    while (number >> power != 0) {
        ++power;
    }
    return (1 << power);
}

//
//  Glass.cpp
//  sph-fluid
//
//  Created by zhou on 5/21/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "Glass.h"
#include "config.h"

Glass::Glass(Vect3f const & origin, Vect3f const & dimension) :
_origin(origin),
_dimension(dimension)
{
    _center = (origin + origin + dimension) * 0.5;
    _walls.push_back(Wall(Vect3f(_center.x, _center.y, _origin.z), Vect3f(0, 0, 1))); // back
    _walls.push_back(Wall(Vect3f(_center.x, _center.y, _origin.z + dimension.z), Vect3f(0, 0, -1))); // front
    _walls.push_back(Wall(Vect3f(_origin.x, _center.y, _center.z), Vect3f(1, 0, 0))); // left
    _walls.push_back(Wall(Vect3f(_origin.x + dimension.x, _center.y, _center.z), Vect3f(-1, 0, 0))); // right
    _walls.push_back(Wall(Vect3f(_center.x, _origin.y, _center.z), Vect3f(0, 1, 0))); // bottom
}

Glass::~Glass()
{
    _walls.clear();
}

Vect3f Glass::origin() const
{
    return _origin;
}

Vect3f Glass::center() const
{
    return _center;
}

Vect3f Glass::dimension() const
{
    return _dimension;
}

std::list<Wall> & Glass::getWalls()
{
    return _walls;
}

Vect3f Glass::collision(Particle &particle)
{
    Vect3f collision(0, 0, 0);
    for (std::list<Wall>::iterator it = _walls.begin(); it != _walls.end(); ++it) {
        Vect3f center = (*it).center;
        Vect3f normal = (*it).normal;
        float f = (center - particle.position).dot(normal) + 0.01;

        if (f > 0.0) {
            collision += GLASS_RESISTANCE * normal * f;
            collision += GLASS_DAMPING * particle.velocity.dot(normal) * normal;
        }
    }
    return collision;
}

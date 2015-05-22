//
//  Glass.cpp
//  sph-fluid
//
//  Created by zhou on 5/21/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "Glass.h"

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

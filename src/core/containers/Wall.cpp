//
//  Wall.cpp
//  sph-fluid
//
//  Created by zhou on 2/3/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "Wall.h"
#include "config.h"

Wall::Wall(const Vect3f& center, const Vect3f& normal)
{
    _center = center;
    _normal = normal;
    _size = BOX_SIZE;
}

Wall::Wall(Wall const & rhs)
{
    _center = rhs._center;
    _normal = rhs._normal;
    _size = rhs._size;
}

Wall::~Wall()
{}

Vect3f & Wall::center()
{
    return _center;
}

Vect3f & Wall::normal()
{
    return _normal;
}

void Wall::draw()
{
}

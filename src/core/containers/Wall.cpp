//
//  Wall.cpp
//  sph-fluid
//
//  Created by zhou on 2/3/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "Wall.h"
#include "config.h"

Wall::Wall(Vect3f const & center, Vect3f const & normal)
{
    this->center = center;
    this->normal = normal;
    size = GRID_SIZE;
    thickness = WALL_THICKNESS;
}

Wall::~Wall()
{
}

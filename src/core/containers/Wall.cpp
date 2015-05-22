//
//  Wall.cpp
//  sph-fluid
//
//  Created by zhou on 2/3/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "Wall.h"
#include "config.h"

Wall::Wall(const Vect3f& c, const Vect3f& n)
{
    center = c;
    normal = n;
    size = GLASS_SIDE_SIZE;
    thickness = GLASS_THICKNESS;
}

Wall::Wall(Wall const & rhs)
{
    center = rhs.center;
    normal = rhs.normal;
    size = rhs.size;
    thickness = rhs.thickness;
}

Wall::~Wall()
{}

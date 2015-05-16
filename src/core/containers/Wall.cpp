//
//  Wall.cpp
//  sph-fluid
//
//  Created by zhou on 2/3/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#define thickness 0.02

#include <GLUT/GLUT.h>

#include "Wall.h"

Wall::Wall(const Vect3f& normal, const Vect3f& center)
{
    _normal = normal;
    _center = center;
    _normal.normalize();
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
    glPushMatrix();
    glTranslated(_center[0], _center[1], _center[2]);
    
    double angle1 = asin(_normal[0]) / (2 * M_PI) * 360.0;
    double angle2 = asin(_normal[1]) / (2 * M_PI) * 360.0;
    
    glRotatef(-angle1, 0, 1, 0);
    glRotatef(-angle2, 1, 0, 0);
    
    glTranslated(0, 0, thickness/2.0);
    glScalef(20,20,1);
    glutSolidCube(thickness);
    
    glPopMatrix();
}


//
//#include "Wall.h"
//#include "config.h"
//
//Wall::Wall(Vect3f const & center, Vect3f const & normal)
//{
//    this->center = center;
//    this->normal = normal;
//    size = GRID_SIZE;
//    thickness = WALL_THICKNESS;
//}
//
//Wall::~Wall()
//{
//}

//
//  GridRender.cpp
//  sph-fluid
//
//  Created by zhou on 2/3/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include <GLUT/GLUT.h>

#include "GridRender.h"
#include "SphFluidDemo.h"
#include "config.h"

GridRender::GridRender()
{}

GridRender::~GridRender()
{}

void GridRender::render()
{
//    std::list<Wall *> walls =SphFluidDemo::instance()->grid.getWalls();
//    for (std::list<Wall *>::iterator it = walls.begin(); it != walls.end(); ++it) {
//        renderWall(*it);
//    }
}

void GridRender::renderWall(Wall * wall)
{
//    Vect3f scale;
//    glPushMatrix();
//
//    glColor4f(0.3, 0.3, 1, 0.1);
//    glEnable (GL_BLEND);
//    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//    glTranslatef(wall->center.x, wall->center.y, wall->center.z);
//    scale.x = (wall->normal.x > 0) ? wall->thickness : wall->size;
//    scale.y = (wall->normal.y > 0) ? wall->thickness : wall->size;
//    scale.z = (wall->normal.z > 0) ? wall->thickness : wall->size;
//    glScalef(scale.x, scale.y, scale.z);
//    glutSolidCube(1);
//
//    glPopMatrix();
}

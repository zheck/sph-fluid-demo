//
//  GlassRender.cpp
//  sph-fluid
//
//  Created by zhou on 2/3/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include <GLUT/GLUT.h>

#include "GlassRender.h"
#include "SphFluidDemo.h"
#include "config.h"

GlassRender::GlassRender()
{}

GlassRender::~GlassRender()
{}

void GlassRender::render(Glass &glass)
{
    std::list<Wall> walls = glass.getWalls();
    for (std::list<Wall>::iterator it = walls.begin(); it != walls.end(); ++it) {
        renderWall(*it);
    }
    
}

void GlassRender::renderWall(Wall & wall)
{
    Vect3f scale;
    glPushMatrix();

    glColor4f(0.3, 0.3, 1, 0.1);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTranslatef(wall.center.x, wall.center.y, wall.center.z);
    scale.x = (wall.normal.x != 0) ? wall.thickness : wall.size;
    scale.y = (wall.normal.y != 0) ? wall.thickness : wall.size;
    scale.z = (wall.normal.z != 0) ? wall.thickness : wall.size;
    glScalef(scale.x, scale.y, scale.z);
    glutSolidCube(1);

    glPopMatrix();
}

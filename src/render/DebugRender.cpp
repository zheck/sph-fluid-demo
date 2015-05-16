//
//  DebugRender.cpp
//  sph-fluid
//
//  Created by zhou on 2/2/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <iostream>
#include <sstream>

#include "DebugRender.h"
#include "SphFluidDemo.h"

DebugRender::DebugRender()
{
    _font = GLUT_BITMAP_TIMES_ROMAN_10;
}

DebugRender::~DebugRender()
{
}

void DebugRender::render()
{
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//
//    gluOrtho2D(0.0, 800.0, 600.0, 0.0);
//    glColor3f(1.0f, 0.0f, 0.0f);
//
//    glRasterPos2i(10, 20);
//    print("Eye position: " + SphFluidDemo::instance()->camera.getEye().getPosition());
//
//    glRasterPos2i(10, 30);
//    print("Target position: " + SphFluidDemo::instance()->camera.getTarget().getPosition());
//
//    glRasterPos2i(10, 40);
//    showNumberOfParticle(SphFluidDemo::instance()->fluidBody.getParticles().size());
//
//    glPopMatrix();
}

void DebugRender::print(std::string str)
{
    char c;

    for (std::string::iterator i = str.begin(); i != str.end(); ++i) {
        c = *i;
        glutBitmapCharacter(_font, c);
    }
}

void DebugRender::showNumberOfParticle(unsigned long numberOfParticle)
{
    std::string str = "Number of particles: ";
    std::stringstream n1;

    n1 << numberOfParticle;
    print(str + n1.str());
}

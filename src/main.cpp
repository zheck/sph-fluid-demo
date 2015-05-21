//
//  main.cpp
//  sph-fluid
//
//  Created by zhou on 12/6/14.
//  Copyright (c) 2014 zhou. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <unistd.h>

#include "SphFluidDemo.h"
#include "config.h"

bool play = false;

void keyboardCallback(unsigned char key, int x, int y)
{
    if (key == 'q') {
        SphFluidDemo::kill();
        exit(0);
    }
    if (key == 'a') {
        play = true;
    }
    SphFluidDemo::instance()->keyboard.update(key, x, y);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SphFluidDemo::instance()->draw();
    glutSwapBuffers();
}

void idleCallback()
{
    if (play == true) {
        SphFluidDemo::instance()->update();
    }
    display();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutCreateWindow("Sph Simulation");

    glutKeyboardFunc(keyboardCallback);
    glutIdleFunc(idleCallback);
    glutDisplayFunc(display);

    glClearColor(164, 164, 164, 1.0);

    glutMainLoop();

    return 0;
}

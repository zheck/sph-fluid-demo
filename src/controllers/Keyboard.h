//
//  Keyboard.h
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Keyboard__
#define __sph_fluid__Keyboard__

#include <stdio.h>
#include <map>

#include "Camera.h"

class Keyboard
{
    std::map<unsigned char, void (Keyboard::*)(void)> _cameraFuncs;

public:
    Keyboard();
    Keyboard(Keyboard const & rhs);
    ~Keyboard();

    Keyboard & operator=(Keyboard const & rhs);

    void update(unsigned char key, int x, int y);

private:
    void zoomIn();
    void zoomOut();
    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();
};

#endif /* defined(__sph_fluid__Keyboard__) */

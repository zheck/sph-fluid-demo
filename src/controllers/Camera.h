//
//  Camera.h
//  sph-fluid
//
//  Created by zhou on 1/19/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Camera__
#define __sph_fluid__Camera__

#include <stdio.h>

#include "Vect3f.h"

class Camera
{
    Vect3f _eye;
    Vect3f _target;
    Vect3f _upVector;
    float _fovy;
    float _angle;
    float _verticalAngle;
    int _distance;

public:
    Camera(float angle, float distance, float fovy);
    Camera(Camera const & rhs);
    ~Camera();

    Camera & operator=(Camera const & rhs);

    void init(Vect3f center, Vect3f up);
    void rotate(float angle);
    void verticalRotate(float angle);
    void zoomIn();
    void zoomOut();
    Vect3f getEye();
    Vect3f getTarget();

private:
    void setCamera();
};

#endif /* defined(__sph_fluid__Camera__) */

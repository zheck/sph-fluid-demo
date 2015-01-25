//
//  Camera.cpp
//  sph-fluid
//
//  Created by zhou on 1/19/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <math.h>
#include <iostream>

#include "Camera.h"
#include "config.h"

Camera::Camera(float angle, float distance, float fovy)
{
    _angle = angle;
    _distance = distance;
    _fovy = fovy;
    _verticalAngle = 0;
}

Camera::~Camera()
{}

void Camera::init(Vect3f eye, Vect3f center, Vect3f up)
{
    _eye = eye;
    _target = center;
    _upVector = up;

    setCamera();
}

void Camera::setCamera()
{
    _eye.x = cosf(_angle) * (_distance * cosf(_verticalAngle)) + _target.x;
    _eye.z = sinf(_angle) * (_distance * cosf(_verticalAngle)) + _target.z;
    _eye.y = _distance * sinf(_verticalAngle) + _target.y;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(_fovy, 800 / 600, 1.0f, 100.0f);
    gluLookAt(_eye.x, _eye.y, _eye.z,
              _target.x, _target.y, _target.z,
              _upVector.x, _upVector.y, _upVector.z);
}

void Camera::zoomIn()
{
    if (_distance > ZOOM_SCALE)
        _distance -= ZOOM_SCALE;
    setCamera();
}

void Camera::zoomOut()
{
    _distance += ZOOM_SCALE;
    setCamera();
}

void Camera::rotate(float angle)
{
    _angle += angle;
    setCamera();
}

void Camera::verticalRotate(float angle)
{
    if (_verticalAngle + angle < 1 && _verticalAngle + angle > -1) {
        _verticalAngle += angle;
        setCamera();
    }
}

Vect3f Camera::getEye()
{
    return _eye;
}

Vect3f Camera::getTarget()
{
    return _target;
}
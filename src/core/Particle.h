//
//  Particle.h
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Particle__
#define __sph_fluid__Particle__

#include <stdio.h>
#include <iostream>
#include <GLUT/GLUT.h>

#include "Vect3f.h"

#include <vector>

class Particle {
    Vect3f _position;
    int _id;
    
public:
    
public:
    Particle(Vect3f const & position, int particleId);
    ~Particle();
    
private:
    Vect3f _velocity;
    Vect3f _force;
    Vect3f _acceleration;
    double _density;
    double _pressure;
    bool _flag;
    
    GLUquadricObj* myQuadric;
    
public:
    Vect3f normal;
    
public:
    
    void draw();
    void clearForce() { _force *= 0; };
    void addForce(Vect3f newForce) { _force += newForce; };
    void calculateAcceleration();
    
    Vect3f& position() { return _position; };
    Vect3f& velocity() { return _velocity; };
    Vect3f& acceleration() { return _acceleration; }
    Vect3f& force()    { return _force; };
    double& density()  { return _density; };
    double& pressure() { return _pressure; };
    bool& flag() { return _flag; };
    int& id() { return _id; };
};

//#include <stdio.h>
//#include <iostream>
//
//#include "Vect3f.h"
//
//class Particle
//{
//public:
//    Vect3f position;
//    Vect3f velocity;
//    Vect3f normal;
//    Vect3f acceleration;
//    float density;
//    float pressure;
//
//public:
//    Particle(Vect3f const & position);
//    Particle(Particle const & rhs);
//    ~Particle();
//
//    Particle & operator=(Particle const & rhs);
//};

#endif /* defined(__sph_fluid__Particle__) */

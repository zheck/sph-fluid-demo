//
//  Vect3f.h
//  sph-fluid
//
//  Created by zhou on 1/19/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Vect3f__
#define __sph_fluid__Vect3f__

#include <stdio.h>
#include <iostream>

class Vect3f
{
public:
    float x;
    float y;
    float z;

public:
    Vect3f();
    Vect3f(float x, float y, float z);
    Vect3f(Vect3f const & rhs);
    ~Vect3f();

    Vect3f & operator=(Vect3f const & rhs);
    Vect3f & operator+=(Vect3f const & rhs);
    Vect3f & operator*=(float f);
    Vect3f operator+(Vect3f const & rhs) const;
    Vect3f operator-(Vect3f const & rhs) const;
    Vect3f operator-(float f) const;
    Vect3f operator*(Vect3f const & rhs) const;
    Vect3f operator*(float f) const;
    Vect3f operator/(float f) const;

    float dot(const Vect3f & rhs) const;
    float magnitude() const;
    Vect3f normalize();

    std::string getPosition() const;
};

inline Vect3f operator*(float f, Vect3f const & lhs)
{
    return Vect3f(lhs.x * f, lhs.y * f, lhs.z * f);
}

#endif /* defined(__sph_fluid__Vect3f__) */

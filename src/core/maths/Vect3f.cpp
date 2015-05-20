//
//  Vect3f.cpp
//  sph-fluid
//
//  Created by zhou on 1/19/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "Vect3f.h"
//
#include <sstream>
#include <iomanip>
#include <math.h>

Vect3f::Vect3f()
{
    x = 0;
    y = 0;
    z = 0;
}

Vect3f::Vect3f(float posx, float posy, float posz)
{
    x = posx;
    y = posy;
    z = posz;
}

Vect3f::Vect3f(Vect3f const & rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

Vect3f::~Vect3f()
{}

Vect3f & Vect3f::operator=(Vect3f const & rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;

    return *this;
}

Vect3f Vect3f::operator+(const Vect3f & rhs) const
{
    return (Vect3f(x + rhs.x, y + rhs.y, z + rhs.z));
}

Vect3f & Vect3f::operator+=(Vect3f const & rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
}

Vect3f & Vect3f::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;

    return *this;
}

Vect3f Vect3f::operator-(const Vect3f & rhs) const
{
    return (Vect3f(x - rhs.x, y - rhs.y, z - rhs.z));
}

Vect3f Vect3f::operator-(float f) const
{
    return (Vect3f(x - f, y - f, z - f));
}

Vect3f Vect3f::operator*(const Vect3f & rhs) const
{
    return Vect3f(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vect3f Vect3f::operator*(float f) const
{
    return Vect3f(x * f, y * f, z * f);
}

Vect3f Vect3f::operator/(float f) const
{
    return Vect3f(x / f, y / f, z / f);
}

float Vect3f::magnitude() const
{
    return sqrt (x * x + y * y + z * z);
}

float Vect3f::dot(const Vect3f &rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

std::string Vect3f::getPosition() const
{
    std::string res = "";
    std::ostringstream ss1, ss2, ss3;

    ss1 << std::fixed << std::setprecision(2) << x;
    res += " x: " + ss1.str();
    ss2 << std::fixed << std::setprecision(2) << y;
    res += " y: " + ss2.str();
    ss3 << std::fixed << std::setprecision(2) << z;
    res += " z: " + ss3.str();

    return res;
}

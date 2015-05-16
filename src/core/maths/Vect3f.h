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
#include <cmath>

class Vect3f {
    
public:
    // Standard constructors
    Vect3f(double x = 0, double y = 0, double z = 0) { this->x = x; this->y = y; this->z = z; }
    
    // Copy constructors & assignment operators
    Vect3f(const Vect3f& v) { *this = v; }
    ~Vect3f();
    Vect3f& operator=(double s) { x = y = z = s; return *this; }
    
    // Access methods
    operator const float*() const { return _element; }
    //    float& operator[](int i) { return _element[i]; }
    
    Vect3f& operator+=(const Vect3f& v)     { x += v.x; y += v.y; z += v.z; return *this; }
    Vect3f& operator-=(const Vect3f& v)     { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vect3f& operator/=(const Vect3f& v)     { x /= v.x; y /= v.y; z /= v.z; return *this; }
    Vect3f& operator/=(const double b)     { x /= b; y /= b; z /= b; return *this; }
    Vect3f& operator*=(const double b)     { x *= b; y *= b; z *= b;   return *this; }
    Vect3f operator+(const Vect3f &b) const { return Vect3f(x+b.x,y+b.y,z+b.z); }
    Vect3f operator-(const Vect3f &b) const { return Vect3f(x-b.x,y-b.y,z-b.z); }
    Vect3f operator*(const double b) const { return Vect3f(x*b,y*b,z*b); }
    Vect3f operator/(const double b) const { return Vect3f(x/b,y/b,z/b); }
    
    // this computes the cross product
    Vect3f operator^(const Vect3f &v) const { return Vect3f(y*v.z-v.y*z,-x*v.z+v.x*z,x*v.y-v.x*y); }
    
    // these are *element-by-element* multiplies, not dot products
    Vect3f operator*(const Vect3f& v) const { return Vect3f(x*v.x,y*v.y,z*v.z); }
    Vect3f& operator*=(const Vect3f& v)     { x *= v.x; y *= v.y; z *= v.z; return *this; }
    
    // *this one* does the dot product
    double dot(const Vect3f &b) const      { return x*b.x+y*b.y+z*b.z; };
    void clear() { double zero = 0.0; x = zero; y = zero; z = zero; };
    
    double magnitude() { return sqrt(x * x + y * y + z * z); };
    Vect3f normalize() {
        double l = x * x +
        y * y +
        z * z;
        if (l != 1.0 && l != 0.0)
        {
            double inv = 1.0 / sqrt(l);
            x *= inv;
            y *= inv;
            z *= inv;
        }
        return *this;
    };
    Vect3f normal() {
        Vect3f a = *this;
        a.normalize();
        return a;
    }
    
    double maxVal() { return x > y && x > z ? x : y > z ? y : z; }
    
    // the data
    union {
        struct { float x,y,z; };
        float _element[3];
    };
};

inline Vect3f operator*(const double a, const Vect3f& b)
{ return Vect3f(b.x * a, b.y * a, b.z * a); }

//#include <stdio.h>
//#include <iostream>
//
//class Vect3f
//{
//public:
//    float x;
//    float y;
//    float z;
//
//public:
//    Vect3f();
//    Vect3f(float x, float y, float z);
//    Vect3f(Vect3f const & rhs);
//    ~Vect3f();
//
//    Vect3f & operator=(Vect3f const & rhs);
//    Vect3f operator+=(Vect3f const & rhs);
//    Vect3f operator+(Vect3f const & rhs) const;
//    Vect3f operator-(Vect3f const & rhs) const;
//    Vect3f operator-(float f) const;
//    Vect3f operator*(Vect3f const & rhs) const;
//    Vect3f operator*(float f) const;
//    Vect3f operator/(float f) const;
//
//    float dot(const Vect3f & rhs) const;
//    float magnitude() const;
//    std::string getPosition() const;
//};

#endif /* defined(__sph_fluid__Vect3f__) */

//
//  Mutex.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/7/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Mutex__
#define __R_TypeServer__Mutex__

#include <iostream>

class Mutex
{
    pthread_mutex_t _lock;
    bool _isLocked; // volatile
    
public:
    Mutex();
    Mutex(Mutex const & rhs);
    ~Mutex();
    
    Mutex & operator=(Mutex const & rhs);
    
    void lock();
    void unlock();
    pthread_mutex_t * getMutex();
};

#endif /* defined(__R_TypeServer__Mutex__) */

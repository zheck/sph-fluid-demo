//
//  Mutex.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/7/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Mutex.hpp"

Mutex::Mutex()
{
    pthread_mutex_init(&_lock, NULL);
    _isLocked = false;
}

Mutex::~Mutex()
{
    if (_isLocked) {
        pthread_mutex_unlock(&_lock);
    }
    pthread_mutex_destroy(&_lock);
}

void Mutex::lock()
{
    pthread_mutex_lock(&_lock);
    _isLocked = true;
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&_lock);
    _isLocked = false;
}

pthread_mutex_t * Mutex::getMutex()
{
    return &_lock;
}
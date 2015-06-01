//
//  Timer.cpp
//  sph-fluid
//
//  Created by zhou on 5/30/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#include "Timer.h"

Timer::Timer()
{}

Timer::~Timer()
{}

void Timer::update(const std::string &name)
{
    gettimeofday(&_timeval, NULL);
    long int time = _timeval.tv_sec * 1000 + _timeval.tv_usec / 1000;

    _times[name] = time;
}

long int Timer::getElapsedTime(const std::string &name)
{
    if (_times.find(name) == _times.end()) {
        _times[name] = 0;
    }
    gettimeofday(&_timeval, NULL);
    long int time = _timeval.tv_sec * 1000 + _timeval.tv_usec / 1000;

    return time - _times[name];
}

//
//  Timer.h
//  sph-fluid
//
//  Created by zhou on 5/30/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Timer__
#define __sph_fluid__Timer__

#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <map>

#include "Singleton.h"

class Timer : public Singleton<Timer>
{
    std::map<std::string, long int> _times;
    struct timeval _timeval;

public:
    Timer();
    Timer(Timer const & rhs);
    ~Timer();

    Timer & operator=(Timer const & rhs);

    long int getElapsedTime(std::string const & name);
    void update(std::string const & name);
};

#endif /* defined(__sph_fluid__Timer__) */

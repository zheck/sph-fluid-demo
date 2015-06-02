//
//  Task.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/7/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Task__
#define __R_TypeServer__Task__

#include <iostream>

class Task
{
    void * _args;
    void (*_ptrFunc)(void *);
    
public:
    Task(void (*ptrFunc)(void *), void * args);
    Task(Task const & rhs);
    ~Task();
    
    Task & operator=(Task const & rhs);
    void operator()();
    void run();
};

#endif /* defined(__R_TypeServer__Task__) */

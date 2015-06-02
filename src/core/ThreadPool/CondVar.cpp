//
//  CondVar.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/7/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "CondVar.hpp"

CondVar::CondVar()
{
    pthread_cond_init(&_condVar, NULL);
}

CondVar::~CondVar()
{
    pthread_cond_destroy(&_condVar);
}

void CondVar::wait(pthread_mutex_t * mutex)
{
    pthread_cond_wait(&_condVar, mutex);
}

void CondVar::signal()
{
    pthread_cond_signal(&_condVar);
}

void CondVar::broadcast()
{
    pthread_cond_broadcast(&_condVar);
}

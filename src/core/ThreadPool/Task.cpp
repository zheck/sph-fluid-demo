//
//  Task.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/7/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Task.hpp"

Task::Task(void (*ptrFunc)(void*), void* args) :
_args(args),
_ptrFunc(ptrFunc)
{}

Task::~Task()
{}

void Task::operator()()
{
    (*_ptrFunc)(_args);
}

void Task::run()
{
    (*_ptrFunc)(_args);
}

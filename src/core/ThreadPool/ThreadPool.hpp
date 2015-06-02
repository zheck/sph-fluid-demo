//
//  ThreadPool.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/4/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__ThreadPool__
#define __R_TypeServer__ThreadPool__

#include <deque>
#include <vector>
#include <iostream>

#include "Task.hpp"
#include "CondVar.hpp"
#include "Mutex.hpp"

class ThreadPool
{
    int _poolSize;
    bool _started;
    std::vector<pthread_t> _threads;
    Mutex _mutex;
    CondVar _condVar;
    std::deque<Task *> _tasks;
    
public:
    ThreadPool(int poolSize);
    ThreadPool(ThreadPool const & rhs);
    ~ThreadPool();
    
    ThreadPool & operator=(ThreadPool const & rhs);
    
    void init();
    void release();
    void * executeThread();
    void addTask(Task * task);
};

void * startThread(void * arg);

#endif /* defined(__R_TypeServer__ThreadPool__) */

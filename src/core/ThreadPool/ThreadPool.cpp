//
//  ThreadPool.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/4/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "ThreadPool.hpp"
#include "Exception.h"

ThreadPool::ThreadPool(int size) :
_poolSize(size)
{}

ThreadPool::~ThreadPool()
{
    release();
}

void ThreadPool::init()
{
    _started = true;

    std::cout << "Initializing threads" << std::endl;
    for (int i = 0; i < _poolSize; ++i) {
        pthread_t id;
        if (pthread_create(&id, NULL, startThread, (void *)this) != 0) {
            throw Exception("Canoot create thread");
        }
        _threads.push_back(id);
    }
    std::cout << "ThreadPool waiting for tasks" << std::endl;
}

void ThreadPool::release()
{
    void * result;
    
    _mutex.lock();
    _started = false;
    _mutex.unlock();
    _condVar.broadcast();
    for (size_t i = 0; i < _threads.size(); ++i) {
        if (pthread_join(_threads[i], &result) != 0) {
            std::cerr << "thread join failed" << std::endl;
        }
//#warning remove or use signal
        _condVar.broadcast();
    }
    std::cout << "ThreadPool released" << std::endl;
}

// Start the thread, wait for condvar to signal that there is a task to be done
void * ThreadPool::executeThread()
{
    Task * task;
    while (true) {
        _mutex.lock();
        while (_started != false && (_tasks.empty())) {
            _condVar.wait(_mutex.getMutex());
        }
        if (_started == false) {
            _mutex.unlock();
            pthread_exit(NULL);
        }
        task = _tasks.front();
        _tasks.pop_front();
        _mutex.unlock();
        (*task)();
    }
    return NULL;
}

void ThreadPool::addTask(Task *task)
{
    _mutex.lock();
    _tasks.push_back(task);
    std::cout << "New task added" << std::endl;
    _condVar.signal();
    _mutex.unlock();
}

// @param ThreadPool arg
void * startThread(void* arg)
{
    ThreadPool* tp = (ThreadPool*)arg;
    tp->executeThread();
    return NULL;
}


//
//  CondVar.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/7/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__CondVar__
#define __R_TypeServer__CondVar__

#include <iostream>

// condition variable that lock/unlock one or all threads
class CondVar
{
    pthread_cond_t _condVar;
    
public:
    CondVar();
    CondVar(CondVar const & rhs);
    ~CondVar();
    
    CondVar & operator=(CondVar const & rhs);
    
    void wait(pthread_mutex_t * mutex);
    void signal();
    void broadcast();
};

#endif /* defined(__R_TypeServer__CondVar__) */


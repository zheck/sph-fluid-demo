//
//  SphFluidDemo.h
//  sph-fluid
//
//  Created by zhou on 12/6/14.
//  Copyright (c) 2014 zhou. All rights reserved.
//

#ifndef __sph_fluid__SphFluidDemo__
#define __sph_fluid__SphFluidDemo__

#include <iostream>

class SplFluidDemo
{
public:
    SplFluidDemo();
    SplFluidDemo(SplFluidDemo const & rhs);
    ~SplFluidDemo();

    SplFluidDemo & operator=(SplFluidDemo const & rhs);

    void run();
};

#endif /* defined(__sph_fluid__SphFluidDemo__) */

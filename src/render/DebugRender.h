//
//  DebugRender.h
//  sph-fluid
//
//  Created by zhou on 2/2/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__DebugRender__
#define __sph_fluid__DebugRender__

#include <stdio.h>

class DebugRender
{
    void * _font;

public:
    DebugRender();
    DebugRender(DebugRender const & rhs);
    ~DebugRender();

    DebugRender & operator=(DebugRender const & rhs);

    void render();
    void print(std::string str);
    void showNumberOfParticle(unsigned long numberOfParticle);
};

#endif /* defined(__sph_fluid__DebugRender__) */

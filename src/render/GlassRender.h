//
//  GlassRender.h
//  sph-fluid
//
//  Created by zhou on 2/3/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__GlassRender__
#define __sph_fluid__GlassRender__

#include <stdio.h>

#include "Wall.h"
#include "Glass.h"

class GlassRender
{
public:
    GlassRender();
    GlassRender(GlassRender const & rhs);
    ~GlassRender();

    GlassRender & operator=(GlassRender const & rhs);

    void render(Glass & glass);
    void renderWall(Wall & wall);
};

#endif /* defined(__sph_fluid__GlassRender__) */

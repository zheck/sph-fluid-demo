//
//  GridRender.h
//  sph-fluid
//
//  Created by zhou on 2/3/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__GridRender__
#define __sph_fluid__GridRender__

#include <stdio.h>

#include "Wall.h"

class GridRender
{
public:
    GridRender();
    GridRender(GridRender const & rhs);
    ~GridRender();

    GridRender & operator=(GridRender const & rhs);

    void render();
    void renderWall(Wall * wall);
};

#endif /* defined(__sph_fluid__GridRender__) */

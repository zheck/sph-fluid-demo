//
//  Mouse.h
//  sph-fluid
//
//  Created by zhou on 1/24/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__Mouse__
#define __sph_fluid__Mouse__

#include <stdio.h>

class Mouse
{
public:
    Mouse();
    Mouse(Mouse const & rhs);
    ~Mouse();

    Mouse & operator=(Mouse const & rhs);
};

#endif /* defined(__sph_fluid__Mouse__) */

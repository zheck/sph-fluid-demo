//
//  Exception.h
//  sph-fluid
//
//  Created by zheck on 02/06/15.
//  Copyright (c) 2015 zheck. All rights reserved.
//

#ifndef __sph_fluid__Exception__
#define __sph_fluid__Exception__

#include <stdio.h>
#include <exception>
#include <iostream>

class Exception : public std::exception
{
    std::string _e;
    
public:
    Exception(std::string const &) throw();
    virtual ~Exception() throw();
    
    Exception & operator=(Exception const &);
    virtual const char * what() const throw();
};

#endif /* defined(__sph_fluid__Exception__) */

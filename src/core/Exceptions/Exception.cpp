//
//  Exception.cpp
//  sph-fluid
//
//  Created by zheck on 02/06/15.
//  Copyright (c) 2015 zheck. All rights reserved.
//

#include "Exception.h"

Exception::Exception(std::string const & msg) throw() : _e(msg)
{}

Exception::~Exception() throw()
{}

const char * Exception::what() const throw() {
    return _e.c_str();
}

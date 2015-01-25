//
//  Singleton.h
//  sph-fluid
//
//  Created by zhou on 1/20/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef sph_fluid_Singleton_h
#define sph_fluid_Singleton_h

template<typename T>
class Singleton
{
private:
    static T * _singleton;

protected:
    Singleton() {}
    Singleton(Singleton const &);
    virtual ~Singleton() {}

    Singleton & operator=(Singleton const &);

public:
    static T * instance();
    static void kill();
};

template<typename T>
T * Singleton<T>::instance() {
    if (_singleton == NULL)
        _singleton = new T;
    return _singleton;
}

template<typename T>
void Singleton<T>::kill() {
    if (_singleton != NULL) {
        delete _singleton;
        _singleton = NULL;
    }
}

template<typename T>
T *Singleton<T>::_singleton = NULL;

#endif

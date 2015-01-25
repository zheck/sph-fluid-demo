//
//  config.h
//  sph-fluid
//
//  Created by zhou on 1/29/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef sph_fluid_config_h
#define sph_fluid_config_h

static const int MAX_PARTICLE = 200;

// 1 unity = 1 mm for now

// GRID
static const int GRID_SIZE = 10; // cm

// PHYSICS

// The constants below and simulation values are based on 1 mole of H2O at perfect stats
// Using source: http://chemistry.about.com/od/moles/a/How-Much-Water-Is-A-Mole-Of-Water.htm
// PARTICLE
static const float PARTICLE_RADIUS = 0.1625; // cm
//static const float PARTICLE_RADIUS = 1.625; // mm
static const float PARTICLE_RENDER_RADIUS = PARTICLE_RADIUS;

//Volume = 18 mL

static const float ROTATION_SCALE = 0.1;
static const int ZOOM_SCALE = 1;
static const float PI = 3.141592;

static const float WALL_THICKNESS = 0.1;

#endif

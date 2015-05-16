//
//  config.h
//  sph-fluid
//
//  Created by zhou on 1/29/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef sph_fluid_config_h
#define sph_fluid_config_h

static const int MAX_PARTICLE = 3;
static const float ROTATION_SCALE = 0.1;
static const int ZOOM_SCALE = 1;
static const float PI = 3.141592;

// 1 unity = 1 mm for now

/* GRID */

static const int GRID_SIZE = 10; // cm
static const float WALL_THICKNESS = 0.1;
static const float WALL_RESISTANCE = 10000.0;
static const float WALL_DAMPING = -1.0;

/* PHYSICS */

static const float GRAVITY = -9.8; // m/s2
static const float WATER_STIFFNESS = 3.0;
static const float SURFACE_THRESHOLD = 10;
static const float SURFACE_TENSION = 0.0728;

/* PARTICLE */
// The constants below and simulation values are based on 1 mole of H2O at perfect stats
// Using source: http://chemistry.about.com/od/moles/a/How-Much-Water-Is-A-Mole-Of-Water.htm
// Volume = 18 mL

//static const float PARTICLE_RADIUS = 0.1625; // cm
static const float PARTICLE_RADIUS = 1.625; // mm
static const float PARTICLE_RADIUS_SQUARE = PARTICLE_RADIUS * PARTICLE_RADIUS;
static const float PARTICLE_RENDER_RADIUS = PARTICLE_RADIUS;
static const float PARTICLE_MASS = 18.0152; // g
static const float PARTICLE_VISCOSITY = 1.308; //
static const float PARTICLE_DENSITY_REST = 0.99829; // g/mm^3 is rest density of water Particle

#endif

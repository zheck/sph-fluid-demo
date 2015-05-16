//
//  config.h
//  sph-fluid
//
//  Created by zhou on 1/29/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef sph_fluid_config_h
#define sph_fluid_config_h


static const float CAMERA_DISTANCE = 2;
static const float CAMERA_ANGLE = 1.5;

static const int NUMBER_OF_PARTICLE_PER_SIDE = 100;
static const float ROTATION_SCALE = 0.1;
static const int ZOOM_SCALE = 1;
static const float PI = 3.141592;
static const float GRID_SIZE = 10;
static const float WALL_THICKNESS = 0.1;

// GRID
static const float BOX_SIZE = 0.4;
static const float WALL_RESISTANCE = 10000.0;
static const float WALL_DAMPING = -1.0;
//#define WALL_K 10000.0 // wall spring constant
//#define WALL_DAMPING -0.9 // wall damping constant


// PHYSICS
static const float GRAVITY = -9.8;
static const float SURFACE_THRESHOLD = 7.065;
static const float SURFACE_TENSION = 0.0728;

// PARTICLE CONFIG FOR 1 MOLE OF H2O
static const float PARTICLE_RENDER_RADIUS = 0.015;
static const float PARTICLE_RADIUS = 0.045;
static const float PARTICLE_RADIUS_SQUARE = PARTICLE_RADIUS * PARTICLE_RADIUS;
static const float PARTICLE_MASS = 0.018; // KG
static const float PARTILE_DENSITY_REST = 998.29; // kg/m^3 is rest density of water Particle
static const float PARTICLE_VISCOSITY = 1.308;

static const float WATER_STIFFNESS = 3.0;

//
//static const int MAX_PARTICLE = 3;
//static const float ROTATION_SCALE = 0.1;
//static const int ZOOM_SCALE = 1;
//static const float PI = 3.141592;
//
//// 1 unity = 1 mm for now
//
///* GRID */
//
//static const int GRID_SIZE = 10; // cm
//static const float WALL_THICKNESS = 0.1;
//static const float WALL_RESISTANCE = 10000.0;
//static const float WALL_DAMPING = -1.0;
//
///* PHYSICS */
//
//static const float GRAVITY = -9.8; // m/s2
//static const float WATER_STIFFNESS = 3.0;
//static const float SURFACE_THRESHOLD = 10;
//static const float SURFACE_TENSION = 0.0728;
//
///* PARTICLE */
//// The constants below and simulation values are based on 1 mole of H2O at perfect stats
//// Using source: http://chemistry.about.com/od/moles/a/How-Much-Water-Is-A-Mole-Of-Water.htm
//// Volume = 18 mL
//
////static const float PARTICLE_RADIUS = 0.1625; // cm
//static const float PARTICLE_RADIUS = 1.625; // mm
//static const float PARTICLE_RADIUS_SQUARE = PARTICLE_RADIUS * PARTICLE_RADIUS;
//static const float PARTICLE_RENDER_RADIUS = PARTICLE_RADIUS;
//static const float PARTICLE_MASS = 18.0152; // g
//static const float PARTICLE_VISCOSITY = 1.308; //
//static const float PARTICLE_DENSITY_REST = 0.99829; // g/mm^3 is rest density of water Particle

#endif

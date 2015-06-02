//
//  config.h
//  sph-fluid
//
//  Created by zhou on 1/29/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef sph_fluid_config_h
#define sph_fluid_config_h

#include <math.h>

/* CAMERA */
static const float CAMERA_DISTANCE = 1.0;
static const float CAMERA_ANGLE = 1.0;
static const float ROTATION_SCALE = 0.1;
static const float ZOOM_SCALE = 0.1;

static const int FPS = 60;

/* PARTICLE */
// The constants below and simulation values are based on 1 mole of H2O at perfect stats (20 C)
// Using source: http://chemistry.about.com/od/moles/a/How-Much-Water-Is-A-Mole-Of-Water.htm

static const int MAX_PARTICLE = 2000;
static const float PARTICLE_DENSITY_REST = 999.97; // kg/m3
static const float PARTICLE_VISCOSITY = 1.002;
static const float PARTICLE_RADIUS = 0.045;
static const float PARTICLE_MASS = 0.02; // kg
static const float WATER_STIFFNESS = 3.0;
static const float PARTICLE_RADIUS_SQUARE = PARTICLE_RADIUS * PARTICLE_RADIUS;
static const float PARTICLE_RENDER_RADIUS = PARTICLE_RADIUS / 2;

enum eParticleStatus
{
    TO_UPDATE,
    STEP1,
    STEP2,
    UPDATED,
};

///* PHYSICS */

static const float GRAVITY = -9.8; // m/s2
static const float SURFACE_THRESHOLD = 7.065;
static const float SURFACE_TENSION = 0.0728;

/* CONTAINER */
static const float GLASS_SIDE_SIZE = 0.5;
static const float GLASS_THICKNESS = 0.001;
static const float GLASS_RESISTANCE = 10000.0;
static const float GLASS_DAMPING = -1;

/* GRID */

static const int GRID_SIZE = ceil(GLASS_SIDE_SIZE / PARTICLE_RADIUS);

#endif

//
//  sph_formulas.h
//  sph-fluid
//
//  Created by zhou on 5/16/15.
//  Copyright (c) 2015 zhou. All rights reserved.
//

#ifndef __sph_fluid__sph_formulas__
#define __sph_fluid__sph_formulas__

#include <stdio.h>

#include "Vect3f.h"

// Official doc: http://matthias-mueller-fischer.ch/publications/sca03.pdf
// But for detailed formulas I use http://nccastaff.bournemouth.ac.uk/jmacey/MastersProjects/MSc11/Rajiv/MasterThesis.pdf
float wpoly6Kernel(float positionSquare); // (3.12)
Vect3f wpoly6KernelGradient(float positionSquare, Vect3f const & spaceDiff); // (3.13)
float wpoly6KernelSecond(float positionSquare); // (3.14)
Vect3f spikyKernelGradient(float positionSquare, Vect3f const & spaceDiff); // (3.15)
float viscosityKernel(float positionSquare); // (3.15)
Vect3f noSymmetricalPressure(float particlePressure,
                            float particleDensity,
                            float neighborPressure,
                            float neighborDensity,
                            Vect3f const & spikyGradient); // (5.4)
Vect3f noSymmetricalViscosity(Vect3f const & velocity,
                             Vect3f const & neighborVelocity,
                             float neighborDensity,
                             float viscosityKernel); // (5,5)

#endif /* defined(__sph_fluid__sph_formulas__) */

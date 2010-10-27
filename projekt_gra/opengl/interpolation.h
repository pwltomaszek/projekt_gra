#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "common.h"
#include "utils.h"

class Interpolation
{
public:
    static float approximateCubicBezierParameter( float atX, float P0_X, float C0_X,
                                                  float C1_X, float P1_X );
    static float* bezierInterpolation( const float &s, const float *p0y, const float *c0y,
                                       const float *c1y, const float *p1y,
                                       const unsigned int &dimensionCount );
};

#endif // INTERPOLATION_H

#include <cmath>

#include "interpolation.h"

float Interpolation::approximateCubicBezierParameter(float atX, float P0_X,
                                                     float C0_X, float C1_X, float P1_X)
{
    // source: http://www.collada.org/public_forum/viewtopic.php?f=12&t=1132
    // author: heinzi

    if (atX - P0_X < VERYSMALL)
       return 0.0;

    if (P1_X - atX < VERYSMALL)
       return 1.0;

    long iterationStep = 0;

    float u = 0.0f;
    float v = 1.0f;

    //iteratively apply subdivision to approach value atX
    while (iterationStep < MAXIMUM_ITERATIONS) {

       // de Casteljau Subdivision.
       double a = (P0_X + C0_X)*0.5f;
       double b = (C0_X + C1_X)*0.5f;
       double c = (C1_X + P1_X)*0.5f;
       double d = (a + b)*0.5f;
       double e = (b + c)*0.5f;
       double f = (d + e)*0.5f; //this one is on the curve!

       //The curve point is close enough to our wanted atX
       if (fabs(f - atX) < APPROXIMATION_EPSILON)
          return clamp((u + v)*0.5f);

       //dichotomy
       if (f < atX) {
          P0_X = f;
          C0_X = e;
          C1_X = c;
          u = (u + v)*0.5f;
       } else {
          C0_X = a;
          C1_X = d;
          P1_X = f;
          v = (u + v)*0.5f;
       }

       iterationStep++;
    }

    return clamp((u + v)*0.5f);
}

float* Interpolation::bezierInterpolation(const float &s, const float *p0y, const float *c0y,
                                          const float *c1y, const float *p1y,
                                          const unsigned int &dimensionCount)
{
    float *values = new float[ dimensionCount ];

    float S = 1 - s;

    for( unsigned int i = 0; i < dimensionCount; ++i )
        values[ i ] = p0y[ i ] * pow( S, 3 ) + \
                      3 * c0y[ i * 2 ] * s * pow( S, 2 ) + \
                      3 * c1y[ i * 2 ] * pow( s, 2 ) * S + \
                      p1y[ i ] * pow( s, 3 );

    return values;
}

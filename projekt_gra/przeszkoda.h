#ifndef PRZESZKODA_H
#define PRZESZKODA_H

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/cartesian2d.hpp>
#include <boost/geometry/geometries/adapted/c_array_cartesian.hpp>

#include "pojazd.h"

class Przeszkoda
{
public:
    Przeszkoda( float dx = 0, float dy = 0 );

    bool koliduje( const Pojazd &przeszkoda );
    virtual void przeliczObszarKolizji( uint x, uint y ) {};
    virtual void rysuj( uint i, uint j ) {}

protected:
    void dzialanie() {};

    boost::geometry::polygon_2d obszarKolizji;
    float dx, dy;
};

#endif // PRZESZKODA_H

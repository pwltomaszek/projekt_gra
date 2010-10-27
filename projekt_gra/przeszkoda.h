#ifndef PRZESZKODA_H
#define PRZESZKODA_H

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/cartesian2d.hpp>
#include <boost/geometry/geometries/adapted/c_array_cartesian.hpp>

class Przeszkoda
{
public:
    bool koliduje( const Przeszkoda &przeszkoda );

protected:
    boost::geometry::polygon_2d poly;
};

#endif // PRZESZKODA_H

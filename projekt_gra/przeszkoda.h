#ifndef PRZESZKODA_H
#define PRZESZKODA_H

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/cartesian2d.hpp>
#include <boost/geometry/geometries/adapted/c_array_cartesian.hpp>

#include "opengl/glmadapter.h"
#include "opengl/opengl.h"

class Pojazd;

class Przeszkoda
{
public:
    Przeszkoda( float rx = 0, float ry = 0, float rz = 0, float dx = 0, float dy = 0 );

    bool koliduje( const Pojazd *pojazd );
    virtual void przeliczObszarKolizji( uint x, uint y ) {}
    virtual void rysuj() {}

    void rysujObszarKolizji();
    void stworzMeshKolizji();
    static bool rysujObszKolizji;

protected:
    void dzialanie( const Pojazd *pojazd ) {}

    boost::geometry::polygon_2d obszarKolizji;
    float przesuniecieX, przesuniecieY;
    float rozmiarX, rozmiarY, rozmiarZ;

    // do testowania
    Mesh *obszarKolizjiMesh;
};

#endif // PRZESZKODA_H

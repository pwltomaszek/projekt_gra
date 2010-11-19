#ifndef PRZESZKODA_H
#define PRZESZKODA_H

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/cartesian2d.hpp>
#include <boost/geometry/geometries/adapted/c_array_cartesian.hpp>

#include "opengl/glmadapter.h"
#include "opengl/opengl.h"

typedef unsigned int uint;
typedef unsigned long int ulint;

class Node;
class Pojazd;

class Przeszkoda
{
public:
    enum Krawedz {
        WSCHOD, ZACHOD, POLNOC, POLUDNIE
    };

    Przeszkoda( float rx = 0, float ry = 0, float rz = 0, float dx = 0, float dy = 0 );

    bool czyKolidujeZPojazdem( const Pojazd *pojazd);
    // mapa zawiera dane: (ktora krawedz dotykamy, z ktorej strony)
    std::map< Krawedz, Krawedz > kolidujaceKrawedzie( const Pojazd *pojazd );
    virtual void przeliczObszarKolizji( uint x, uint y ) {}
    virtual void rysuj();

    void rysujObszarKolizji();
    void stworzMeshKolizji();
    static bool rysujObszKolizji;    




protected:
    void virtual dzialanie( const Pojazd *pojazd ) {}
    boost::geometry::polygon_2d obszarKolizji;
    float przesuniecieX, przesuniecieY;
    float rozmiarX, rozmiarY, rozmiarZ;


    bool koliduje;    

    // do testowania
    Mesh *obszarKolizjiMesh;
    Node *mMesh;   
};

#endif // PRZESZKODA_H

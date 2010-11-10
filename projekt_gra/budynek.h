#ifndef BUDYNEK_H
#define BUDYNEK_H

#include "obiektnamapie.h"
#include "przeszkoda.h"

class Node;

class Budynek : public Przeszkoda
{
private:
    //dx, dy - rozmiar; x, y - polozenie na mapie
//    , x, y;
    uint szer, dl;

public:
    Budynek();
    Budynek( uint szer, uint dl, float dx, float dy );
    virtual void rysuj( uint i, uint j );
    virtual void przeliczObszarKolizji( uint x, uint y );

    static Node *mesh;
};

#endif // BUDYNEK_H

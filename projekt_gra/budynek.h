#ifndef BUDYNEK_H
#define BUDYNEK_H

#include "obiektnamapie.h"
#include "przeszkoda.h"

class Node;

class Budynek : public Przeszkoda
{
public:
    Budynek( uint rx, uint ry, float dx = 0, float dy = 0 );
    virtual void rysuj();
    virtual void przeliczObszarKolizji( uint x, uint y );

    static Node *mesh;
};

#endif // BUDYNEK_H

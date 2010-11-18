#ifndef BUDYNEK_H
#define BUDYNEK_H

#include "przeszkoda.h"

class Node;

class Budynek : public Przeszkoda
{
public:
    Budynek( uint rx, uint ry, uint rz, float dx = 0, float dy = 0 );
    virtual void przeliczObszarKolizji( uint x, uint y );
};

#endif // BUDYNEK_H

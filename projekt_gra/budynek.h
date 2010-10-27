#ifndef BUDYNEK_H
#define BUDYNEK_H

#include "obiektnamapie.h"
#include "przeszkoda.h"

class Node;

class Budynek : public ObiektNaMapie,
                public Przeszkoda
{
public:
    Budynek();
    virtual void rysuj( uint i, uint j );
    void przeliczObszarKolizji();

    unsigned int dx, dy, x, y;

    static Node *mesh;
};

#endif // BUDYNEK_H

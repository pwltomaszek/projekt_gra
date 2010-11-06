#ifndef BUDYNEK_H
#define BUDYNEK_H

#include "obiektnamapie.h"
#include "przeszkoda.h"

class Node;

class Budynek : public ObiektNaMapie,
                public Przeszkoda
{
private:
    //dx, dy - rozmiar; x, y - polozenie na mapie
    unsigned int dx, dy, x, y;

public:
    Budynek();
    Budynek( int dx, int dy, int x, int y );
    virtual void rysuj( uint i, uint j );
    void przeliczObszarKolizji();

    static Node *mesh;
};

#endif // BUDYNEK_H

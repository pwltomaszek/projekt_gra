#ifndef DROGA_H
#define DROGA_H

#include "przeszkoda.h"

class Node;

class Droga : public Przeszkoda
{
public:
    enum Kierunek {
        PolnocPoludnie,
        WschodZachod
    };

    Droga( Kierunek kierunek, float rx, float ry );
    virtual void rysuj();

    static Node *mesh;

private:
    enum Kierunek kierunek;
};

#endif // DROGA_H

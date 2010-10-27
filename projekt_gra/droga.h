#ifndef DROGA_H
#define DROGA_H

#include "obiektnamapie.h"

class Node;

class Droga : public ObiektNaMapie
{
public:
    enum Kierunek {
        PolnocPoludnie,
        WschodZachod
    } kierunek;

    Droga();

    virtual void rysuj(uint i, uint j);

    static Node *mesh;
};

#endif // DROGA_H

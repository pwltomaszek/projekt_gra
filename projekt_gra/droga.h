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
    };

    Droga();
    Droga( Kierunek kierunek );
    virtual void rysuj(uint i, uint j);

    static Node *mesh;

private:
    enum Kierunek kierunek;
};

#endif // DROGA_H

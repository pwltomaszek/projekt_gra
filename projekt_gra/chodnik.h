#ifndef CHODNIK_H
#define CHODNIK_H

#include "obiektnamapie.h"

class Node;

class Chodnik : public ObiektNaMapie
{
public:
    Chodnik();
    virtual void rysuj(uint i, uint j);

    static Node *mesh;
};

#endif // CHODNIK_H

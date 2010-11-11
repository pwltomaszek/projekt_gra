#ifndef CHODNIK_H
#define CHODNIK_H

#include "przeszkoda.h"

class Node;

class Chodnik : public Przeszkoda
{
public:
    Chodnik( float rx, float ry );
    virtual void rysuj();

    static Node *mesh;
};

#endif // CHODNIK_H

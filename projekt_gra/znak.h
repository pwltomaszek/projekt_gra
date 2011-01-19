#ifndef ZNAK_H
#define ZNAK_H
#include "przeszkoda.h"
class Node;

class Znak : public Przeszkoda
{
public:
    Znak( float dx = 0, float dy = 0 );
    virtual void przeliczObszarKolizji( uint x, uint y );
};

#endif // ZNAK_H

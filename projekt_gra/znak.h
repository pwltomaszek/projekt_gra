#ifndef ZNAK_H
#define ZNAK_H

#include <QString>

#include "przeszkoda.h"
class Node;

class Znak : public Przeszkoda
{
public:
    Znak( float dx, float dy, const QString &rodzaj, float obrot );
    virtual void przeliczObszarKolizji( uint x, uint y );
};

#endif // ZNAK_H

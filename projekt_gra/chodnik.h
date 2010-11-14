#ifndef CHODNIK_H
#define CHODNIK_H

#include "przeszkoda.h"

class Node;

class Chodnik : public Przeszkoda
{
public:
    Chodnik( float rx, float ry );
};

#endif // CHODNIK_H

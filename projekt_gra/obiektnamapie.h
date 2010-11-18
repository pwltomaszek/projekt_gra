#ifndef OBIEKTNAMAPIE_H
#define OBIEKTNAMAPIE_H

#include "przeszkoda.h"
class Przeszkoda;

typedef unsigned int uint;

class ObiektNaMapie
{
public:
    ObiektNaMapie();
    ObiektNaMapie( uint x, uint y );
    ObiektNaMapie( Przeszkoda *przeszkoda, uint x, uint y );

    Przeszkoda *przeszkoda;
    uint x, y;
};

#endif // OBIEKTNAMAPIE_H

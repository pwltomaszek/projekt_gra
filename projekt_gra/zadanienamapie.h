#ifndef ZADANIENAMAPIE_H
#define ZADANIENAMAPIE_H

#include "zadaniaKontrolne/zadaniekontrolne.h"
class ZadanieKontrolne;

typedef unsigned int uint;

class ZadanieNaMapie
{
public:
    ZadanieNaMapie();
    ZadanieNaMapie( uint x, uint y );
    ZadanieNaMapie( ZadanieKontrolne *zadanie, uint x, uint y );

    ZadanieKontrolne *zadanie;
    uint x, y;
};

#endif // ZADANIENAMAPIE_H

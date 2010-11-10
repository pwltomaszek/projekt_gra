#ifndef OBIEKTNAMAPIE_H
#define OBIEKTNAMAPIE_H

typedef unsigned int uint;

class ObiektNaMapie
{
public:
    ObiektNaMapie();
    virtual void rysuj( uint i, uint j ) = 0;

    float dx, dy;
};

#endif // OBIEKTNAMAPIE_H

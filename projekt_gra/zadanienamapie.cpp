#include "zadanienamapie.h"

#include "opengl/opengl.h"

ZadanieNaMapie::ZadanieNaMapie()
{
    x = y = 0;
}

ZadanieNaMapie::ZadanieNaMapie(uint x, uint y)
{
    this->x = x;
    this->y = y;
}

ZadanieNaMapie::ZadanieNaMapie(ZadanieKontrolne *zadanie, uint x, uint y)
{
    this->zadanie = zadanie;
    this->x = x;
    this->y = y;
}

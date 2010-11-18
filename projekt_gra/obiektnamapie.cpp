#include "obiektnamapie.h"

#include "opengl/opengl.h"

ObiektNaMapie::ObiektNaMapie()
{
    x = y = 0;
}

ObiektNaMapie::ObiektNaMapie(uint x, uint y)
{
    this->x = x;
    this->y = y;
}

ObiektNaMapie::ObiektNaMapie(Przeszkoda *przeszkoda, uint x, uint y)
{
    this->przeszkoda = przeszkoda;
    this->x = x;
    this->y = y;
}

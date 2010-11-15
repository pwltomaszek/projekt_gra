#ifndef DROGA_H
#define DROGA_H

#include "przeszkoda.h"

class Droga : public Przeszkoda
{
public:
    enum Kierunek {
        PolnocPoludnie,
        WschodZachod,
        Skrzyzowanie
    };

    Droga( Kierunek kierunek, float rx, float ry );

private:
    enum Kierunek kierunek;
};

#endif // DROGA_H

#ifndef PUNKTKONTROLNY_H
#define PUNKTKONTROLNY_H

#include "przeszkoda.h"
#include "powiazaniezadan.h"
#include "zadaniekontrolne.h"


class PunktKontrolny : public ZadanieKontrolne
{
public:
    PunktKontrolny();
    PunktKontrolny(uint szer, uint dl, float dx = 0, float dy = 0);

    void przeliczObszarKolizji(uint x, uint y);
    void dzialanie( const Pojazd *pojazd );
};




#endif // PUNKTKONTROLNY_H

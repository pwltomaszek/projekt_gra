#ifndef ZATRZYMANIEKONTROLNE_H
#define ZATRZYMANIEKONTROLNE_H

#include "przeszkoda.h"
#include "zadaniekontrolne.h"
#include "powiazaniezadan.h"

class ZatrzymanieKontrolne : public ZadanieKontrolne
{
public:
    ZatrzymanieKontrolne( RodzajDichromatyzmu rd, int wartoscDichromatyzmu,
                          uint szer, uint dl, float dx = 0, float dy = 0);

    void przeliczObszarKolizji(uint x, uint y);
    void dzialanie( const Pojazd *pojazd );
};

#endif // ZATRZYMANIEKONTROLNE_H

#ifndef POLEKONTROLNE_H
#define POLEKONTROLNE_H

#include "przeszkoda.h"
#include "powiazanieZadan.h"
#include "zadaniekontrolne.h"

class PoleKontrolne : public ZadanieKontrolne
{
public:    
    PoleKontrolne();
    PoleKontrolne(uint szer, uint dl, float dx = 0, float dy = 0);

    void przeliczObszarKolizji(uint x, uint y);
    void dzialanie( const Pojazd *pojazd );
};

#endif // POLEKONTROLNE_H

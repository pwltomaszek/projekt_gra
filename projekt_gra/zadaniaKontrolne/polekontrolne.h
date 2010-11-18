#ifndef POLEKONTROLNE_H
#define POLEKONTROLNE_H

#include "przeszkoda.h"
#include "powiazaniezadan.h"
#include "zadaniekontrolne.h"

class PoleKontrolne : public ZadanieKontrolne
{
public:    
    PoleKontrolne();
    PoleKontrolne(Przeszkoda::Krawedz krWe, Przeszkoda::Krawedz krWy,
                  uint szer, uint dl, float dx = 0, float dy = 0);

    void przeliczObszarKolizji(uint x, uint y);
    void dzialanie( const Pojazd *pojazd );


    bool wjechanoOk, wyjechanoOk, pierwszeWjechanie;
    Przeszkoda::Krawedz krWe, krWy;
};

#endif // POLEKONTROLNE_H

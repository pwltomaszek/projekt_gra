#ifndef POLEKONTROLNE_H
#define POLEKONTROLNE_H

#include "przeszkoda.h"
#include "powiazanieZadan.h"
#include "zadaniekontrolne.h"

class PoleKontrolne : public ZadanieKontrolne
{
public:    
    PoleKontrolne();
    enum krawedz {
        WSCHOD, ZACHOD, POLNOC, POLUDNIE
    };
    PoleKontrolne(krawedz krWe, krawedz krWy, uint szer, uint dl, float dx = 0, float dy = 0);

    void przeliczObszarKolizji(uint x, uint y);
    void dzialanie( const Pojazd *pojazd );


    bool wjechanoOk, wyjechanoOk;
    krawedz krWe, krWy;
};

#endif // POLEKONTROLNE_H

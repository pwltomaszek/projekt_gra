#ifndef POLEKONTROLNE_H
#define POLEKONTROLNE_H

#include "przeszkoda.h"
#include "powiazaniezadan.h"
#include "zadaniekontrolne.h"

class PoleKontrolne : public ZadanieKontrolne
{
public:    
    PoleKontrolne();
    PoleKontrolne( RodzajDichromatyzmu rd, int wartoscDichromatyzmu,
                  Przeszkoda::Krawedz krWe, Przeszkoda::Krawedz krWy,
                  float ogrMin, float ogrMax, uint szer, uint dl, float dx = 0, float dy = 0);

    void przeliczObszarKolizji(uint x, uint y);
    void dzialanie( const Pojazd *pojazd );


    bool wjechanoOk, wyjechanoOk, pierwszeWjechanie;
    Przeszkoda::Krawedz krWe, krWy;

    bool porownajKrawedzie( const Pojazd *pojazd, const Krawedz kr );



    float ograniczenieMax, ograniczenieMin;
    ulint liczbaProbek, liczbaProbekPoprawnych;
    float sumaPredkosci;
};

#endif // POLEKONTROLNE_H

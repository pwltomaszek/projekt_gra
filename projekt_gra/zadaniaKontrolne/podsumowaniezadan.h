#ifndef PODSUMOWANIEZADAN_H
#define PODSUMOWANIEZADAN_H

#include "przeszkoda.h"
#include "zadaniaKontrolne/zadaniekontrolne.h"

class PodsumowanieZadan : public Przeszkoda
{
public:
    PodsumowanieZadan();
    PodsumowanieZadan(std::vector< ZadanieKontrolne* >zadania,
                      uint szer, uint dl, float dx = 0, float dy = 0);

    void przeliczObszarKolizji(uint x, uint y);
    void dzialanie( const Pojazd *pojazd );

    bool osiagnietoMete;
    bool sprawdzajKolizje;

    std::vector< ZadanieKontrolne* > zadania;

    int punktyProtanopii, punktyDeuteranopii, punktyTritanopii;
};

#endif // PODSUMOWANIEZADAN_H

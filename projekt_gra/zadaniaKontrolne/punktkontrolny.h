#ifndef PUNKTKONTROLNY_H
#define PUNKTKONTROLNY_H

#include "przeszkoda.h"
#include "powiazaniezadan.h"
#include "zadaniekontrolne.h"

class ZadanieKontrolne;

class PunktKontrolny : public ZadanieKontrolne
{
public:
    PunktKontrolny();
    PunktKontrolny(bool dobryPunkt, RodzajDichromatyzmu rd, int wartoscDichromatyzmu,
                   uint szer, uint dl, float dx = 0, float dy = 0);

    void przeliczObszarKolizji(uint x, uint y);
    void dzialanie( const Pojazd *pojazd );

    bool dobryPunkt; // okresla czy gracz powinien natrafic na ten punkt
};




#endif // PUNKTKONTROLNY_H

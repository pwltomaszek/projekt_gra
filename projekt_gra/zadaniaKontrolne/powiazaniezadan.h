#ifndef POWIAZANIEZADAN_H
#define POWIAZANIEZADAN_H

#include "przeszkoda.h"
#include "zadaniaKontrolne/zadaniekontrolne.h"

class ZadanieKontrolne;

class PowiazanieZadan
{
  public:
    PowiazanieZadan();

    std::vector< ZadanieKontrolne* > zadaniaPowiazane;

    //void powiazZadania(std::vector< ZadanieKontrolne* > zadaniaPowiazane);
    void powiazZadania();
    void ustawSprawdzanieKolizji( bool r );
};

#endif // POWIAZANIEZADAN_H

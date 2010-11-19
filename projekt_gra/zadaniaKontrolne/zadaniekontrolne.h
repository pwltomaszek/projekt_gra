#ifndef ZADANIEKONTROLNE_H
#define ZADANIEKONTROLNE_H

#include "przeszkoda.h"
#include "powiazaniezadan.h"

class PowiazanieZadan;

class ZadanieKontrolne : public virtual Przeszkoda
{
public:
    ZadanieKontrolne();

    bool zadanieAktywowane;
    bool zadanieZaliczonePoprawnie;

    PowiazanieZadan *kontenerPowiazania;
    bool sprawdzajKolizje;
};

#endif // ZADANIEKONTROLNE_H

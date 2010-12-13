#ifndef ZADANIEKONTROLNE_H
#define ZADANIEKONTROLNE_H

#include "przeszkoda.h"
#include "powiazaniezadan.h"

class PowiazanieZadan;

class ZadanieKontrolne : public virtual Przeszkoda
{
public:
    enum RodzajDichromatyzmu {
        PROTANOPIA, DEUTERANOPIA, TRITANOPIA
    };

    ZadanieKontrolne();
    ZadanieKontrolne( RodzajDichromatyzmu rodzajDichromatyzmu, int wartoscDichromatyzmu );

    bool zadanieAktywowane;
    bool zadanieZaliczonePoprawnie;

    PowiazanieZadan *kontenerPowiazania;
    bool sprawdzajKolizje;

    RodzajDichromatyzmu rodzajDichromatyzmu;    //okresla rodzaj choroby, z jaka zwozane jest zadanie
    int wartoscDichromatyzmu;                   //okresla jak wazne jest zadanie dla rozpoznania choroby:
                                                // 0 - niewazne; >0 - istotne w zaleznosci od wartosci
};

#endif // ZADANIEKONTROLNE_H

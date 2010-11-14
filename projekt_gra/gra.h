#ifndef GRA_H
#define GRA_H

#include <QTime>

#include <map>

#include "mapa.h"
#include "pojazd.h"
#include <QKeyEvent>
class GLWrapper;

class Gra
{
public:
    Gra();

    void klawiszWcisniety( int klawisz );
    void klawiszZwolniony( int klawisz );
    void petla();
    void rysuj();

    enum Akcje { SKRET_LEWO, SKRET_PRAWO, W_PRZOD, W_TYL, HAMOWANIE,
                 ZMIANA_KAMERY, PODSWIETLENIE_OBSZ_KOLIZJI };
    QMap<int, Akcje> akcje;

private:
    void przesunGracza();
    void przetworzLogikeGry();

    Mapa mMapa;
    Pojazd mPojazd, m2, m3, m4, m5, m6, m7;

    std::map< int, bool > mKlawisze;

    QTime mTimer;
    double mCurrentTime;
    double mTimeDelta;

    //to do usuniecia
    enum widoki {
        Z_GORY, FPP, PSYCHO, KONIEC
    };
    enum widoki widok;
};

#endif // GRA_H

#ifndef GRA_H
#define GRA_H

#include <boost/timer.hpp>

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

    enum Akcje { SKRET_LEWO, SKRET_PRAWO, W_PRZOD, W_TYL, HAMOWANIE, ZMIANA_KAMERY };
    QMap<int, Akcje> akcje;



private:
    void przesunGracza();
    void przetworzLogikeGry();

    Mapa mMapa;
    Pojazd mPojazd;

    std::map< int, bool > mKlawisze;

    boost::timer mTimer;
    double mCurrentTime;
    double mTimeDelta;




    //to do usuniecia
    enum widoki {
        Z_GORY, FPP, PSYCHO, KONIEC
    };
    enum widoki widok;
};

#endif // GRA_H

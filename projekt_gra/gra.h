#ifndef GRA_H
#define GRA_H

#include <map>

#include "mapa.h"
#include "pojazd.h"

class GLWrapper;

class Gra
{
public:
    Gra();

    void klawiszWcisniety( int klawisz, bool nacisniety = true );
    void petla();
    void rysuj();

private:
    void przetworzKlawisze();
    void przetworzLogikeGry();

    Mapa mMapa;
    Pojazd mPojazd;

    std::map< int, bool > mKlawisze;

    // w sekundach!
    double mTimeDelta;

    //to do usuniecia
    bool widokZGory, widokTwarz;
};

#endif // GRA_H

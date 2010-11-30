#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include "zadanienamapie.h"
#include "zadaniaKontrolne/podsumowaniezadan.h"

typedef unsigned int uint;

class Pojazd;
class Przeszkoda;
class ZadanieKontrolne;
class ZadanieNaMapie;

class Mapa
{
public:
    Mapa();

    void dodajPrzeszkode( Przeszkoda *przeszkoda, uint x, uint y );
    void dodajZadanie( ZadanieKontrolne *przeszkoda, uint x = 0, uint y = 0 );
    void dodajIPowiazZadania( std::vector< ZadanieNaMapie* > obiekty );

    bool zachodziKolizjaFizyczna( const Pojazd *pojazd );
    bool zachodziKolizjaZZadaniem( const Pojazd *pojazd );
    void rysuj();

private:
    std::vector< Przeszkoda* > mapa[ 100 ][ 100 ];
    std::vector< Przeszkoda* > przeszkody;
    std::vector< ZadanieKontrolne* > zadania;
};

#endif // MAPA_H

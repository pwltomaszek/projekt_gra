#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include "obiektnamapie.h"


typedef unsigned int uint;

class Pojazd;
class Przeszkoda;
class ZadanieKontrolne;
class ObiektNaMapie;

class Mapa
{
public:
    Mapa();

    void dodajPrzeszkode( Przeszkoda *przeszkoda, uint x, uint y );
    void dodajZadanie( ZadanieKontrolne *przeszkoda, uint x = 0, uint y = 0 );
    void dodajIPowiazZadania( std::vector< ObiektNaMapie* > obiekty );

    bool zachodziKolizjaFizyczna( const Pojazd *pojazd );
    bool zachodziKolizjaZZadaniem( const Pojazd *pojazd );
    void rysuj();

private:
    std::vector< Przeszkoda* > mapa[ 100 ][ 100 ];
    std::vector< Przeszkoda* > przeszkody, zadania;
    std::vector<ObiektNaMapie *> obiekty;
};

#endif // MAPA_H

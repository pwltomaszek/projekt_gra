#ifndef MAPA_H
#define MAPA_H

#include <vector>

typedef unsigned int uint;

class ObiektNaMapie;
class Pojazd;
class Przeszkoda;

class Mapa
{
public:
    Mapa();

//    ObiektNaMapie* mapa[ 5 ][ 3 ];    // x, y

    void dodajPrzeszkode( Przeszkoda *przeszkoda, uint x = 0, uint y = 0 );

    bool zachodziKolizjaFizyczna( const Pojazd *pojazd );
    bool zachodziKolizjaZZadaniem( const Pojazd *pojazd );
    void rysuj();
//    void ustawPrzeszkody();

private:
//    std::vector< Przeszkoda* > zad;
    std::vector< Przeszkoda* > mapa[ 100 ][ 100 ];
    std::vector< Przeszkoda* > przeszkody;
};

#endif // MAPA_H

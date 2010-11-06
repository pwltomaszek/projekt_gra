#ifndef MAPA_H
#define MAPA_H

#include <vector>

class ObiektNaMapie;
class Przeszkoda;

class Mapa
{
public:
    Mapa();

    ObiektNaMapie* mapa[ 5 ][ 3 ];    // x, y

    bool zachodziKolizja( const Przeszkoda *przeszkoda );
    void rysuj();
    void ustawPrzeszkody();

private:
    std::vector< Przeszkoda* > przeszkody;
};

#endif // MAPA_H

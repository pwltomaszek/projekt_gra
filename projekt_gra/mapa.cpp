#include "budynek.h"
#include "chodnik.h"
#include "droga.h"
#include "mapa.h"
#include "punktkontrolny.h"

#include <cstring>

Mapa::Mapa()
{
    memset( mapa, 0, 15 * sizeof( ObiektNaMapie* ) );

    //budynki
    Budynek *b1 = new Budynek;
    b1->dx = 20;
    b1->dy = 1;
    b1->x = 0;
    b1->y = 0;
    b1->przeliczObszarKolizji();
    mapa[ 0 ][ 0 ] = b1;
    przeszkody.push_back( b1 );

    Budynek *b2 = new Budynek;
    b2->dx = 2;
    b2->dy = 1;
    b2->x = 0;
    b2->y = 2;
    b2->przeliczObszarKolizji();
    mapa[ 0 ][ 2 ] = b2;
    przeszkody.push_back( b2 );

    //chodniki
    Chodnik *ch = new Chodnik;
    mapa[ 0 ][ 1 ] = ch;
    mapa[ 4 ][ 1 ] = ch;
    mapa[ 4 ][ 2 ] = ch;
    mapa[ 2 ][ 2 ] = ch;

    //drogi
    Droga *dWZ = new Droga;
    dWZ->kierunek = Droga::WschodZachod;
    mapa[ 3 ][ 2 ] = dWZ;

    Droga *dPP = new Droga;
    dPP->kierunek = Droga::PolnocPoludnie;
    mapa[ 1 ][ 1 ] = dPP;
    mapa[ 2 ][ 1 ] = dPP;
    mapa[ 3 ][ 1 ] = dPP;
}

void Mapa::rysuj()
{
    for( int i = 0; i < 5; ++i )
        for( int j = 0; j < 3; ++j )
            if( mapa[ i ][ j ] )
                mapa[ i ][ j ]->rysuj( i, j );
}

bool Mapa::zachodziKolizja(const Przeszkoda *przeszkoda)
{
    for( unsigned int i = 0; i < przeszkody.size(); ++i )
        if( przeszkody.at( i )->koliduje( *przeszkoda ) )
            return true;

    return false;
}

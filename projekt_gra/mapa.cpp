#include "budynek.h"
#include "chodnik.h"
#include "droga.h"
#include "mapa.h"
#include "punktkontrolny.h"

#include <cstring>

Mapa::Mapa()
{
//    memset( mapa, 0, 15 * sizeof( vector< Przeszkoda* > ) );

    //budynki
    dodajPrzeszkode( new Budynek( 20, 1 ), 0, 0 );
    dodajPrzeszkode( new Budynek( 2, 1 ), 0, 2 );
//    dodajPrzeszkode( new Chodnik );

    //chodniki
    Chodnik *ch = new Chodnik;
    mapa[ 0 ][ 1 ] = ch;
    mapa[ 4 ][ 1 ] = ch;
    mapa[ 4 ][ 2 ] = ch;
    mapa[ 2 ][ 2 ] = ch;

    //drogi
    Droga *dWZ = new Droga( Droga::WschodZachod );
    mapa[ 3 ][ 2 ] = dWZ;

    Droga *dPP = new Droga( Droga::PolnocPoludnie );
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

bool Mapa::zachodziKolizja(const Pojazd *pojazd)
{
    bool check = false;
    for( unsigned int i = 0; i < przeszkody.size(); ++i )
        if( przeszkody.at( i )->koliduje( *pojazd ) )
            check= true;

    return check;
}

void Mapa::dodajPrzeszkode(Przeszkoda *przeszkoda, uint x, uint y)
{
    przeszkody.push_back( przeszkoda );
    przeszkoda->przeliczObszarKolizji( x, y );
    mapa[x][y].push_back(przeszkoda);
}

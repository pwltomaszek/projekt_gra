#include "budynek.h"
#include "chodnik.h"
#include "droga.h"
#include "mapa.h"
#include "punktkontrolny.h"

Mapa::Mapa()
{
//    memset( mapa, 0, 15 * sizeof( vector< Przeszkoda* > ) );

    //budynki
    dodajPrzeszkode( new Budynek( 20, 1 ) );
    dodajPrzeszkode( new Budynek( 2, 1 ), 0, 2 );

    //chodniki
    dodajPrzeszkode( new Chodnik( 1, 1 ), 0, 1 );
    dodajPrzeszkode( new Chodnik( 1, 2 ), 4, 1 );
    dodajPrzeszkode( new Chodnik( 1, 1 ), 2, 2 );

//    //drogi
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 1, 1 ), 3, 2 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 3, 1 ), 1, 1 );
}

void Mapa::rysuj()
{
    GLWrapper &gl = GLWrapper::instance();

    for( int i = 0; i < 5; ++i ) {
        for( int j = 0; j < 3; ++j ) {
            gl.pushMatrix();
            gl.translate( glm::vec3( i, j, 0.f ) );

            for( uint k = 0; k < mapa[ i ][ j ].size(); ++k )
                mapa[ i ][ j ].at( k )->rysuj();

            gl.popMatrix();
        }
    }
}

bool Mapa::zachodziKolizja(const Pojazd *pojazd)
{
    bool check = false;
    for( unsigned int i = 0; i < przeszkody.size(); ++i )
        if( przeszkody.at( i )->koliduje( pojazd ) )
            check = true;

    return check;
}

void Mapa::dodajPrzeszkode(Przeszkoda *przeszkoda, uint x, uint y)
{
    przeszkody.push_back( przeszkoda );
    przeszkoda->przeliczObszarKolizji( x, y );
    mapa[ x ][ y ].push_back(przeszkoda);
}

#include "budynek.h"
#include "chodnik.h"
#include "droga.h"
#include "mapa.h"
#include "punktkontrolny.h"

Mapa::Mapa()
{
//    memset( mapa, 0, 15 * sizeof( vector< Przeszkoda* > ) );

    //budynki

    dodajPrzeszkode( new Budynek( 20, 4 ), 6, 5 );
    dodajPrzeszkode( new Budynek( 20, 4 ), 0, 0 );

   // dodajPrzeszkode( new Budynek( 2, 1 ), 0, 2 );

    //chodniki
//    dodajPrzeszkode( new Chodnik( 20, 1 ), 0, 5 );
//    dodajPrzeszkode( new Chodnik( 20, 2 ), 0, 12 );

////    //drogi
//    dodajPrzeszkode( new Droga( Droga::WschodZachod, 1, 1 ), 3, 2 );
//    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 50, 6 ), 0, 6 );

    //dodajPrzeszkode( new PunktKontrolny );
}

void Mapa::rysuj()
{
    GLWrapper &gl = GLWrapper::instance();

    for( int i = 0; i < 100; ++i ) {
        for( int j = 0; j < 100; ++j ) {
            for( uint k = 0; k < mapa[ i ][ j ].size(); ++k ) {
                mapa[ i ][ j ].at( k )->rysujObszarKolizji();

                gl.pushMatrix();
                gl.translate( glm::vec3( i, j, 0.f ) );

                mapa[ i ][ j ].at( k )->rysuj();

                gl.popMatrix();
            }
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
    przeszkoda->stworzMeshKolizji();
    mapa[ x ][ y ].push_back(przeszkoda);
}

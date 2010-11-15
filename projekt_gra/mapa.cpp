#include <QDebug>

#include "budynek.h"
#include "chodnik.h"
#include "droga.h"
#include "mapa.h"
#include "zadaniaKontrolne/punktkontrolny.h"


Mapa::Mapa()
{
//    memset( mapa, 0, 15 * sizeof( vector< Przeszkoda* > ) );

    //budynki
    dodajPrzeszkode( new Budynek( 100, 4, 1 ), 0, 0 );

    //chodniki - najlepiej by caly obszar byl chodnikiem, a reszta obiektow go nadrysowala
    dodajPrzeszkode( new Chodnik( 50, 1 ), 0, 12 );
    dodajPrzeszkode( new Chodnik( 44, 1 ), 56, 12 );
    dodajPrzeszkode( new Chodnik( 100, 2 ), 0, 4 );

    //drogi
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 50, 6 ), 0, 6 );
    dodajPrzeszkode( new Droga( Droga::Skrzyzowanie, 6, 6 ), 50, 6 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 44, 6 ), 56, 6 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 6, 20 ), 50, 12 );


    //zadania kontrolne
    dodajPrzeszkode( new PunktKontrolny(1, 6), 59, 6);
    dodajPrzeszkode( new PunktKontrolny(6, 1), 50, 15);
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

bool Mapa::zachodziKolizjaFizyczna(const Pojazd *pojazd)
{
   // bool check = false;
    for( unsigned int i = 0; i < przeszkody.size(); ++i )
        if( dynamic_cast<Budynek*>(przeszkody.at( i )) != NULL
                && przeszkody.at( i )->czyKolidujeZPojazdem( pojazd ) )
            return true;

    return false;
}

bool Mapa::zachodziKolizjaZZadaniem(const Pojazd *pojazd)
{
    for( unsigned int i = 0; i < przeszkody.size(); ++i )
        if( dynamic_cast<PunktKontrolny*>(przeszkody.at( i )) != NULL
                && przeszkody.at( i )->czyKolidujeZPojazdem( pojazd ) );
           //przeszkody.at( i )->dzialanie( pojazd );

      return NULL;
}

void Mapa::dodajPrzeszkode(Przeszkoda *przeszkoda, uint x, uint y)
{
    przeszkody.push_back( przeszkoda );
    przeszkoda->przeliczObszarKolizji( x, y );
    przeszkoda->stworzMeshKolizji();
    mapa[ x ][ y ].push_back(przeszkoda);
}

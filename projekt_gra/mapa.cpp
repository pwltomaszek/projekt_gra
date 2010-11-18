#include <QDebug>

#include "budynek.h"
#include "chodnik.h"
#include "droga.h"
#include "mapa.h"
#include "zadaniaKontrolne/punktkontrolny.h"
#include "zadaniaKontrolne/powiazanieZadan.h"
#include "zadaniaKontrolne/polekontrolne.h"


Mapa::Mapa()
{
    //budynki
    dodajPrzeszkode( new Budynek( 100, 4, 1 ), 0, 0 );

    //chodniki - najlepiej by caly obszar byl chodnikiem, a reszta obiektow go nadrysowala
    dodajPrzeszkode( new Chodnik( 50, 1 ), 0, 12 );
    dodajPrzeszkode( new Chodnik( 44, 1 ), 56, 12 );
    dodajPrzeszkode( new Chodnik( 100, 2 ), 0, 4 );

    //drogi
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 50, 6 ), 0, 6 );
    dodajPrzeszkode( new Droga( Droga::Skrzyzowanie, 6, 6 ), 50, 6 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 64, 6 ), 56, 6 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 6, 20 ), 50, 12 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 70, 6 ), 50, 30 );


    //zadania kontrolne - punkty
    obiekty.push_back( new ObiektNaMapie(new PunktKontrolny(1, 6), 59, 6 ) );
    obiekty.push_back( new ObiektNaMapie(new PunktKontrolny(6, 1), 50, 15 ) );
    dodajIPowiazZadania( obiekty );

    obiekty.clear();
    obiekty.push_back( new ObiektNaMapie(new PunktKontrolny(1, 6), 10, 6 ) );
    obiekty.push_back( new ObiektNaMapie(new PunktKontrolny(1, 6), 20, 6 ) );
    obiekty.push_back( new ObiektNaMapie(new PunktKontrolny(1, 6), 30, 6 ) );
    dodajIPowiazZadania( obiekty );

    //zadania kontrolne - pola
    obiekty.clear();
    obiekty.push_back( new ObiektNaMapie(new PoleKontrolne(PoleKontrolne::ZACHOD, PoleKontrolne::WSCHOD, 30, 6), 70, 30 ) );
    obiekty.push_back( new ObiektNaMapie(new PoleKontrolne(PoleKontrolne::ZACHOD, PoleKontrolne::WSCHOD, 30, 6), 70, 6 ) );
    dodajIPowiazZadania( obiekty );
}

void Mapa::dodajIPowiazZadania(std::vector<ObiektNaMapie *> obiekty) {
    ZadanieKontrolne *zk;
    PowiazanieZadan *pZ = new PowiazanieZadan;
    foreach(ObiektNaMapie *el, obiekty){
        zk = dynamic_cast<ZadanieKontrolne*>(el->przeszkoda);
        pZ->zadaniaPowiazane.push_back(zk);
        dodajZadanie( zk, el->x, el->y );
    }
    pZ->powiazZadania();

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
    for( unsigned int i = 0; i < przeszkody.size(); ++i )
        if( przeszkody.at( i )->czyKolidujeZPojazdem( pojazd ) )
            return true;

    return false;
}

bool Mapa::zachodziKolizjaZZadaniem(const Pojazd *pojazd)
{
    for( unsigned int i = 0; i < zadania.size(); ++i )
        if( zadania.at( i )->czyKolidujeZPojazdem( pojazd ) );

      return NULL;
}

void Mapa::dodajPrzeszkode( Przeszkoda *przeszkoda, uint x, uint y )
{
    przeszkody.push_back( przeszkoda );
    przeszkoda->przeliczObszarKolizji( x, y );
    przeszkoda->stworzMeshKolizji();
    mapa[ x ][ y ].push_back(przeszkoda);
}

void Mapa::dodajZadanie(ZadanieKontrolne *zadanieK, uint x, uint y)
{
    zadania.push_back( zadanieK );
    zadanieK->przeliczObszarKolizji( x, y );
    zadanieK->stworzMeshKolizji();
    mapa[ x ][ y ].push_back(zadanieK);
}

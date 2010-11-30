#include <QDebug>

#include "budynek.h"
#include "chodnik.h"
#include "droga.h"
#include "mapa.h"
#include "zadaniaKontrolne/punktkontrolny.h"
#include "zadaniaKontrolne/powiazaniezadan.h"
#include "zadaniaKontrolne/polekontrolne.h"
#include "zadaniaKontrolne/podsumowaniezadan.h"

Mapa::Mapa()
{
    /*
    ** ZABUDOWANIA */
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


    /*
    ** ZADANIA KONTROLNE */
    std::vector<ZadanieNaMapie *> zadaniaNaMapie;

    //punkty (np. odnogi skrzyzowan)
    zadaniaNaMapie.push_back( new ZadanieNaMapie(
                                 new PunktKontrolny(true, ZadanieKontrolne::TRITANOPIA, 0, 1, 6), 59, 6 ) );
    zadaniaNaMapie.push_back( new ZadanieNaMapie(
                                 new PunktKontrolny(false, ZadanieKontrolne::TRITANOPIA, 1, 6, 1), 50, 15 ) );
    dodajIPowiazZadania( zadaniaNaMapie );

    //pola (np. ograniczniki predkosci)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie( new PoleKontrolne( ZadanieKontrolne::DEUTERANOPIA, 2,
                                                                    PoleKontrolne::ZACHOD, PoleKontrolne::WSCHOD,
                                                                    10, 50, 30, 6), 70, 30 ) );
    zadaniaNaMapie.push_back( new ZadanieNaMapie (new PoleKontrolne( ZadanieKontrolne::DEUTERANOPIA, 2,
                                                                    PoleKontrolne::ZACHOD, PoleKontrolne::WSCHOD,
                                                                    40, 100, 30, 6), 70, 6 ) );
    dodajIPowiazZadania( zadaniaNaMapie );


    /*
    ** META */
    dodajPrzeszkode(new PodsumowanieZadan( zadania, 5, 5), 90, 90 );
}

void Mapa::dodajIPowiazZadania(std::vector<ZadanieNaMapie *> zadaniaNaMapie) {
    ZadanieKontrolne *zk;
    PowiazanieZadan *pZ = new PowiazanieZadan;
    foreach(ZadanieNaMapie *el, zadaniaNaMapie){
        zk = dynamic_cast<ZadanieKontrolne*>(el->zadanie);
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

#include <QDebug>

#include "budynek.h"
#include "chodnik.h"
#include "droga.h"
#include "mapa.h"
#include "zadaniaKontrolne/punktkontrolny.h"
#include "zadaniaKontrolne/powiazaniezadan.h"
#include "zadaniaKontrolne/polekontrolne.h"
#include "zadaniaKontrolne/zatrzymaniekontrolne.h"
#include "zadaniaKontrolne/podsumowaniezadan.h"

Mapa::Mapa()
{
    /*
    ** ZABUDOWANIA */
    //budynki
    dodajPrzeszkode( new Budynek( 100, 4, 40 ), 50, 0 );

    //chodniki - najlepiej by caly obszar byl chodnikiem, a reszta obiektow go nadrysowala
    dodajPrzeszkode( new Chodnik( 50, 1 ), 0, 25 );

    //drogi
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 150, 6 ), 0, 10 );

    dodajPrzeszkode( new Droga( Droga::Skrzyzowanie, 6, 6 ), 150, 10 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 6, 50 ), 150, 16 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 70, 6 ), 156, 60 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 80, 6 ), 156, 10 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 6, 15 ), 236, 1 );

    dodajPrzeszkode( new Droga( Droga::Skrzyzowanie, 12, 12 ), 226, 60 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 12, 246 ), 226, 70 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 150, 12 ), 238, 304 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 150, 12 ), 238, 60 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 6, 244 ), 388, 60 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 6, 30 ), 229, 33 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 80, 6 ), 235, 33 );

    dodajPrzeszkode( new Droga( Droga::Skrzyzowanie, 6, 12 ), 388, 304 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 30, 12 ), 394, 304 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 6, 70 ), 424, 246 );

    dodajPrzeszkode( new Droga( Droga::Skrzyzowanie, 6, 6 ), 424, 240 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 120, 6 ), 430, 240 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 6, 206 ), 550, 40 );
    dodajPrzeszkode( new Droga( Droga::PolnocPoludnie, 6, 212 ), 424, 30 );
    dodajPrzeszkode( new Droga( Droga::WschodZachod, 116, 6 ), 430, 30 );

    dodajPrzeszkode( new Droga( Droga::Skrzyzowanie, 20, 20 ), 546, 20 );

    /** ### podreczny FAQ tworzenia zadan ###
    * PoleKontrolne( RodzajDichromatyzmu rd, int wartoscDichromatyzmu,
    *              Przeszkoda::Krawedz krWe, Przeszkoda::Krawedz krWy,
    *              float ogrMin, float ogrMax, uint szer, uint dl, float dx = 0, float dy = 0 )
    * PunktKontrolny( bool dobryPunkt, RodzajDichromatyzmu rd, int wartoscDichromatyzmu,
    *               uint szer, uint dl, float dx = 0, float dy = 0 )
    */


    /*####################################################################################*/
    /*####################################################################################*/
    /*####################################################################################*/
    /* ## ZADANIA KONTROLNE ## - podzia³ na 3 etapy dla kazdej z chorob */
    std::vector<ZadanieNaMapie *> zadaniaNaMapie;

    /*####################################################################################*/
    /*# ETAP I: PROTANOPIA # */
    //pola (np. ograniczniki predkosci)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie( new PoleKontrolne( ZadanieKontrolne::PROTANOPIA, 1,
                                                                    PoleKontrolne::ZACHOD, PoleKontrolne::WSCHOD,
                                                                    5, 30, 50, 8), 60, 9 ) );
    dodajIPowiazZadania( zadaniaNaMapie );

    //punkty (np. odnogi skrzyzowan)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie(
                                 new PunktKontrolny(true, ZadanieKontrolne::PROTANOPIA, 0, 8, 1), 149, 30 ) );
    zadaniaNaMapie.push_back( new ZadanieNaMapie(
                                 new PunktKontrolny(false, ZadanieKontrolne::PROTANOPIA, 1, 1, 8), 170, 9 ) );

    dodajIPowiazZadania( zadaniaNaMapie );

    //zatrzymania (np. przed przejsciami dla pieszych)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie( new ZatrzymanieKontrolne( ZadanieKontrolne::PROTANOPIA, 1,
                                                                    20, 10), 210, 58 ) );
    dodajIPowiazZadania( zadaniaNaMapie );

    /*####################################################################################*/
    /*# ETAP II: DEUTERANOPIA # */
    //pola (np. ograniczniki predkosci)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie( new PoleKontrolne( ZadanieKontrolne::DEUTERANOPIA, 1,
                                                                    PoleKontrolne::POLUDNIE, PoleKontrolne::POLNOC,
                                                                    10, 70, 14, 150), 225, 100 ) );
    zadaniaNaMapie.push_back( new ZadanieNaMapie( new PoleKontrolne( ZadanieKontrolne::DEUTERANOPIA, 1,
                                                                    PoleKontrolne::POLUDNIE, PoleKontrolne::POLNOC,
                                                                    10, 70, 8, 150), 387, 100 ) );
    dodajIPowiazZadania( zadaniaNaMapie );

    //punkty (np. odnogi skrzyzowan)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie(
                                 new PunktKontrolny(true, ZadanieKontrolne::DEUTERANOPIA, 0, 14, 1), 225, 80 ) );
    zadaniaNaMapie.push_back( new ZadanieNaMapie(
                                 new PunktKontrolny(false, ZadanieKontrolne::DEUTERANOPIA, 1, 1, 14), 260, 59 ) );
    zadaniaNaMapie.push_back( new ZadanieNaMapie(
                                 new PunktKontrolny(false, ZadanieKontrolne::DEUTERANOPIA, 1, 8, 1), 228, 46 ) );
    dodajIPowiazZadania( zadaniaNaMapie );

    //zatrzymania (np. przed przejsciami dla pieszych)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie( new ZatrzymanieKontrolne( ZadanieKontrolne::DEUTERANOPIA, 1,
                                                                    30, 30), 370, 290 ) );
    dodajIPowiazZadania( zadaniaNaMapie );


    /*####################################################################################*/
    /*# ETAP III: TRITANOPIA # */
    //pola (np. ograniczniki predkosci)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie( new PoleKontrolne( ZadanieKontrolne::TRITANOPIA, 1,
                                                                    PoleKontrolne::POLNOC, PoleKontrolne::POLUDNIE,
                                                                    10, 50, 8, 100), 549, 80 ) );
    zadaniaNaMapie.push_back( new ZadanieNaMapie( new PoleKontrolne( ZadanieKontrolne::TRITANOPIA, 1,
                                                                    PoleKontrolne::POLNOC, PoleKontrolne::POLUDNIE,
                                                                    10, 50, 8, 100), 423, 80 ) );
    dodajIPowiazZadania( zadaniaNaMapie );

    //punkty (np. odnogi skrzyzowan)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie(
                                 new PunktKontrolny(false, ZadanieKontrolne::TRITANOPIA, 1, 1, 8), 450, 239 ) );
    zadaniaNaMapie.push_back( new ZadanieNaMapie(
                                 new PunktKontrolny(true, ZadanieKontrolne::TRITANOPIA, 0, 8, 1), 423, 220 ) );
    dodajIPowiazZadania( zadaniaNaMapie );

    //zatrzymania (np. przed przejsciami dla pieszych)
    zadaniaNaMapie.clear();
    zadaniaNaMapie.push_back( new ZadanieNaMapie( new ZatrzymanieKontrolne( ZadanieKontrolne::TRITANOPIA, 1,
                                                                    8, 20), 423, 246 ) );
    dodajIPowiazZadania( zadaniaNaMapie );

    /*####################################################################################*/
    /* META */
    dodajPrzeszkode(new PodsumowanieZadan( zadania, 20, 20 ), 546, 20 );
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

    for( int i = 0; i < 600; ++i ) {
        for( int j = 0; j < 400; ++j ) {
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

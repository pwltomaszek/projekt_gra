#include "pojazd.h"
#include "polekontrolne.h"
#include <QDebug>

PoleKontrolne::PoleKontrolne()
{
}

PoleKontrolne::PoleKontrolne(Przeszkoda::Krawedz krWe, Przeszkoda::Krawedz krWy,
                             uint szer, uint dl, float dx, float dy)
    : Przeszkoda( szer, dl, 0, dx, dy )
{
    wjechanoOk = wyjechanoOk = false;
    pierwszeWjechanie = true;
    this->krWe = krWe;
    this->krWy = krWy;
    sprawdzajKolizje = true;
}

void PoleKontrolne::dzialanie(const Pojazd *pojazd) {
    std::map< Krawedz, Krawedz > krawedzie = kolidujaceKrawedzie(pojazd);

    //cialo bedzie wygladalo mniej-wiecej tak:
//    if( wjechanoOk ){
//        qDebug() << "wjechano w PoleK";
//        zliczanie predkosci, zabawy z timerem. co tam bedzie potrzeba
//    }
//    if( wjechanoOk && wyjechanoOk ){
//        qDebug() << "wyjechano w PoleK po uprzednio dobrym wjechaniu ";
//    }

    //jak juz wjechano i wyjechano w porzadku, nastapi deazyktywacja tego zadania i z nim powiazanych.
    //ewentualnie w poprzednim warunku. zrobie jak trzeba, gdy bede mial mozliwosc sprawdzania kolizji z krawedziami
    if( sprawdzajKolizje == true && koliduje == true ){
        sprawdzajKolizje = false;

        //qDebug() << "zaliczono PoleK. z nim i jego powiaznymi nie beda wiecej sprawdzane kolizje";
        foreach(ZadanieKontrolne* el, kontenerPowiazania->zadaniaPowiazane)
            el->sprawdzajKolizje = false;
    }
}

void PoleKontrolne::przeliczObszarKolizji(uint x, uint y)
{
    float coords[ 5 ][ 2 ] = { { 0.0, 0.0 },
                               { (float)rozmiarX, 0.0 },
                               { (float)rozmiarX, (float)rozmiarY },
                               { 0.0, (float)rozmiarY },
                               { 0.0, 0.0 } };
    for( int i = 0; i < 5; ++i ) {
        coords[ i ][ 0 ] += x + przesuniecieX;
        coords[ i ][ 1 ] += y + przesuniecieY;
    }

    assign( obszarKolizji, coords );
    correct( obszarKolizji );
}

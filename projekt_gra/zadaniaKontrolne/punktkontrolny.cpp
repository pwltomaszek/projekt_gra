#include <QDebug>

#include "punktkontrolny.h"

PunktKontrolny::PunktKontrolny(uint szer, uint dl, float dx, float dy)
    : Przeszkoda( szer, dl, 0, dx, dy )
{
    sprawdzajKolizje = true;
}

void PunktKontrolny::dzialanie(const Pojazd *pojazd){
    //warunek moze zostac spelniony tylko raz w grze
    if( sprawdzajKolizje == true && koliduje == true ){
        sprawdzajKolizje = false;

        //TU ustawiac punkty karmy
        qDebug() << "wjechano w PunktK. z nim i jego powiaznymi nie beda wiecej sprawdzane kolizje";
        foreach(ZadanieKontrolne* el, kontenerPowiazania->zadaniaPowiazane)
            el->sprawdzajKolizje = false;
    }
}

void PunktKontrolny::przeliczObszarKolizji(uint x, uint y)
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


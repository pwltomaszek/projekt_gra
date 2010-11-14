#include <QDebug>

#include "punktkontrolny.h"

PunktKontrolny::PunktKontrolny(uint szer, uint dl, float dx, float dy)
    : Przeszkoda( szer, dl, 0, dx, dy )
{
}

void PunktKontrolny::dzialanie(const Pojazd *pojazd){
    if( this->koliduje == true ){
        //qDebug() << "koliduje z zadaniem";
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

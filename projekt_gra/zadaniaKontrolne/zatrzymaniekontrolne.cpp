#include "zatrzymaniekontrolne.h"
#include "pojazd.h"
#include <QDebug>

ZatrzymanieKontrolne::ZatrzymanieKontrolne( RodzajDichromatyzmu rd, int wartoscDichromatyzmu,
                                            uint szer, uint dl, float dx, float dy )
 : Przeszkoda( szer, dl, 0, dx, dy ), ZadanieKontrolne( rd, wartoscDichromatyzmu )
{
    sprawdzajKolizje = true;
}

void ZatrzymanieKontrolne::dzialanie(const Pojazd *pojazd) {

    if( sprawdzajKolizje &&  zadanieAktywowane && !koliduje ){
        zadanieZaliczonePoprawnie = false;
        qDebug() << "nie zatrzymano siê";
        qDebug() << "zaliczono poprawnie: " << zadanieZaliczonePoprawnie;

        foreach(ZadanieKontrolne* el, kontenerPowiazania->zadaniaPowiazane){
                el->sprawdzajKolizje = false;
        }
    }else if( sprawdzajKolizje && koliduje ){
        if(!zadanieAktywowane)
            qDebug() << "wjechano w obszar zatrzymania";

        zadanieAktywowane = true;
        if( sprawdzajKolizje && koliduje ){
            if(pojazd->predkoscView < 1){
                zadanieZaliczonePoprawnie = true;
                sprawdzajKolizje = false;
                qDebug() << "zatrzymano siê";
                qDebug() << "zaliczono poprawnie: " << zadanieZaliczonePoprawnie;
            }
        }
    }
}


void ZatrzymanieKontrolne::przeliczObszarKolizji(uint x, uint y)
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

#include <QDebug>

#include "podsumowaniezadan.h"


PodsumowanieZadan::PodsumowanieZadan( std::vector< ZadanieKontrolne* >zadania,
                                     uint szer, uint dl, float dx, float dy)
    : Przeszkoda( szer, dl, 0, dx, dy )
{
    osiagnietoMete = false;
    sprawdzajKolizje = true;
    this->zadania = zadania;

    punktyProtanopii = punktyDeuteranopii = punktyTritanopii = 0;
}
void PodsumowanieZadan::dzialanie(const Pojazd *pojazd) {

    if( sprawdzajKolizje && koliduje ){
        qDebug()<< "\n### META ###";
        osiagnietoMete = true;
        sprawdzajKolizje = false;

        foreach (ZadanieKontrolne *el, zadania) {
            if ( el->zadanieAktywowane && !el->zadanieZaliczonePoprawnie )
                switch( el->rodzajDichromatyzmu ){
                    case ZadanieKontrolne::RodzajDichromatyzmu::PROTANOPIA:
                        punktyProtanopii += el->wartoscDichromatyzmu;
                        break;
                    case ZadanieKontrolne::RodzajDichromatyzmu::DEUTERANOPIA:
                        punktyDeuteranopii += el->wartoscDichromatyzmu;
                        break;
                    case ZadanieKontrolne::RodzajDichromatyzmu::TRITANOPIA:
                        punktyTritanopii += el->wartoscDichromatyzmu;
                        break;
                    default: ;
                }
        }

        qDebug()<<"punktyProtanopii: " << punktyProtanopii;
        qDebug()<<"punktyDeuteranopii: " << punktyDeuteranopii;
        qDebug()<<"punktyTritanopii: " << punktyTritanopii;
    }

}


void PodsumowanieZadan::przeliczObszarKolizji(uint x, uint y)
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

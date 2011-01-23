#include <QDebug>
#include <QMessageBox>

#include "podsumowaniezadan.h"


PodsumowanieZadan::PodsumowanieZadan( std::vector< ZadanieKontrolne* >zadania,
                                     uint szer, uint dl, float dx, float dy)
    : Przeszkoda( szer, dl, 0, dx, dy )
{
    osiagnietoMete = false;
    sprawdzajKolizje = true;
    this->zadania = zadania;

    punktyProtanopii = punktyDeuteranopii = punktyTritanopii = 0;
    zadanProtanopii = zadanDeuteranopii = zadanTritanopii = 0;
}
void PodsumowanieZadan::dzialanie(const Pojazd *pojazd) {

    if( sprawdzajKolizje && koliduje ){
        qDebug()<< "\n### META ###";
        osiagnietoMete = true;
        sprawdzajKolizje = false;

        foreach (ZadanieKontrolne *el, zadania) {
            if ( el->zadanieAktywowane){
                switch( el->rodzajDichromatyzmu ){
                    case ZadanieKontrolne::RodzajDichromatyzmu::PROTANOPIA:
                        zadanProtanopii++;
                        break;
                    case ZadanieKontrolne::RodzajDichromatyzmu::DEUTERANOPIA:
                        zadanDeuteranopii++;
                        break;
                    case ZadanieKontrolne::RodzajDichromatyzmu::TRITANOPIA:
                        zadanTritanopii++;
                        break;
                    default: ;
                }
                if (!el->zadanieZaliczonePoprawnie )
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
        }

        qDebug()<<"# ilosc poprawnie zaliczonych zadan / ilosc przejechanych zadan"
                   <<" (powinno byc po x/3. jesli jest mniej, to znaczy ze czesc zadan ominieto).";
        qDebug()<<"punktyProtanopii: " << zadanProtanopii - punktyProtanopii << "/" << zadanProtanopii;
        qDebug()<<"punktyDeuteranopii: " << zadanDeuteranopii - punktyDeuteranopii << "/" << zadanDeuteranopii;
        qDebug()<<"punktyTritanopii: " << zadanTritanopii - punktyTritanopii << "/" << zadanTritanopii;

        std::stringstream wiadomosc;
        wiadomosc << "Ilosc poprawnie zaliczonych zadan / ilosc przejechanych zadan\n";
        wiadomosc << "(Powinno byc po x/3. Jesli jest mniej, to znaczy ze czesc zadan ominieto).\n\n";
        wiadomosc <<"Punkty protanopii: " << zadanProtanopii - punktyProtanopii << "/" << zadanProtanopii;
        if(zadanProtanopii > 0)
            wiadomosc << " (poprawnosc: " << ((float)zadanProtanopii - (float)punktyProtanopii) / (float)zadanProtanopii * 100<< "%)\n";
        else wiadomosc << " (poprawnosc: nieokreslona) \n";

        wiadomosc <<"Punkty deuteranopii: " << zadanDeuteranopii - punktyDeuteranopii << "/" << zadanDeuteranopii;
        if(zadanDeuteranopii > 0)
            wiadomosc << " (poprawnosc: " << ((float)zadanDeuteranopii - (float)punktyDeuteranopii) / (float)zadanDeuteranopii * 100 << "%)\n";
        else wiadomosc << " (poprawnosc: nieokreslona) \n";

        wiadomosc <<"Punkty tritanopii: " << zadanTritanopii - punktyTritanopii << "/" << zadanTritanopii;
        if(zadanTritanopii > 0)
            wiadomosc <<" (poprawnosc: " << ((float)zadanTritanopii - (float)punktyTritanopii) / (float)zadanTritanopii * 100 << "%)\n";
        else wiadomosc << " (poprawnosc: nieokreslona) \n";

        QMessageBox::information(0, "Koniec gry", QString::fromStdString(wiadomosc.str()), QMessageBox::Ok);
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

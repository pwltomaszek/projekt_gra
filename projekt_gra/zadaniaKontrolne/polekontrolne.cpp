#include "pojazd.h"
#include "polekontrolne.h"
#include <QDebug>

#define PROCENT_POPRAWNOSCI     80.0

PoleKontrolne::PoleKontrolne()
{
}

PoleKontrolne::PoleKontrolne( RodzajDichromatyzmu rd, int wartoscDichromatyzmu,
                             Przeszkoda::Krawedz krWe, Przeszkoda::Krawedz krWy, float ogrMin, float ogrMax,
                             uint szer, uint dl, float dx, float dy)
    : Przeszkoda( szer, dl, 0, dx, dy ), ZadanieKontrolne( rd, wartoscDichromatyzmu )
{
    wjechanoOk = wyjechanoOk = false;
    pierwszeWjechanie = true;
    this->krWe = krWe;
    this->krWy = krWy;
    this->ograniczenieMax = ogrMax;
    this->ograniczenieMin = ogrMin;
    sprawdzajKolizje = true;
    liczbaProbek = liczbaProbekPoprawnych = 0;
    sumaPredkosci = 0;

}

void PoleKontrolne::dzialanie(const Pojazd *pojazd) {

    //jesli gracz wiechal ze zlej strony, to zadanie zostanie zaliczone negayuwnie
    if( sprawdzajKolizje &&  zadanieAktywowane && !koliduje ){
        zadanieAktywowane = true;
        zadanieZaliczonePoprawnie = false;
        qDebug() << "wyjechano z trasy przed koncem testu.";
        qDebug() << "zaliczono poprawnie: " << zadanieZaliczonePoprawnie;

        foreach(ZadanieKontrolne* el, kontenerPowiazania->zadaniaPowiazane){
                el->sprawdzajKolizje = false;
        }
    }else if( sprawdzajKolizje && koliduje ){

        if( !wjechanoOk && porownajKrawedzie( pojazd, krWe ) ){     //badanie poprawnego wjazdu            
            wjechanoOk = true;
            zadanieAktywowane = true;
            qDebug() << "\n### wjechano w PunktK. z nim i jego powiaznymi nie beda wiecej sprawdzane kolizje";

            foreach(ZadanieKontrolne* el, kontenerPowiazania->zadaniaPowiazane){
                if (el != this)
                    el->sprawdzajKolizje = false;
            }
        }else if( wjechanoOk && !wyjechanoOk && porownajKrawedzie( pojazd, krWy ) ){ //badanie poprawnego wyjazdu
            float sredniaPredkosc = sumaPredkosci/liczbaProbek;
            float procentPoprawnosc = static_cast<float>(liczbaProbekPoprawnych)/static_cast<float>(liczbaProbek)*100;
            qDebug() << "predkosc srednia pokonania odcinka: " << sredniaPredkosc
                        << "km/h (wymagany zakres: " << ograniczenieMin << "-" << ograniczenieMax <<")";
            qDebug() << "probek poprawnych/wszystkich: " << liczbaProbekPoprawnych << "/" << liczbaProbek
                     << " -> procent poprawnosc: " << procentPoprawnosc
                     << "% (wymagane minimum: " << PROCENT_POPRAWNOSCI << "%)";

            if( procentPoprawnosc > PROCENT_POPRAWNOSCI
                    && sredniaPredkosc < ograniczenieMax && sredniaPredkosc > ograniczenieMin ){
                zadanieZaliczonePoprawnie = true;
            }else zadanieZaliczonePoprawnie = false;

            qDebug() << "zaliczono poprawnie: " << zadanieZaliczonePoprawnie;

            wyjechanoOk = true;
            sprawdzajKolizje = false;
        }else{                          //kiedy pojazd jest w srodku zadania...
            liczbaProbek++;
            sumaPredkosci += pojazd->predkoscView;
            if( pojazd->predkoscView < ograniczenieMax && pojazd->predkoscView > ograniczenieMin )
                liczbaProbekPoprawnych++;
        }
    }

}

//porownuje dana krawedz z krawedziemi z ktorymi aktualnie koliduje pojazd
//TODO: sprawic by nie rozpoczeto zliczania po wjezdzie 'od srodka'. sprawdzic warunek
//i dezaktywawac 'sprawdzajKolizje' lub zrobic niezalezna zmienna dla tej akcji
bool PoleKontrolne::porownajKrawedzie( const Pojazd *pojazd, const Krawedz kr ){
    std::map< Krawedz, Krawedz > krawedzie = kolidujaceKrawedzie(pojazd);
    for (std::map< Krawedz, Krawedz >::iterator kIt = krawedzie.begin(); kIt != krawedzie.end(); ++kIt) {
        if( kr == kIt->first )
            return true;
    }
    return false;
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

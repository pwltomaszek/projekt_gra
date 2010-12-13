#include "zadaniekontrolne.h"

ZadanieKontrolne::ZadanieKontrolne(){
    zadanieAktywowane = false;
    wartoscDichromatyzmu = 0;
}

ZadanieKontrolne::ZadanieKontrolne(RodzajDichromatyzmu rodzajDichromatyzmu, int wartoscDichromatyzmu ){
    zadanieAktywowane = false;
    this->wartoscDichromatyzmu = wartoscDichromatyzmu;
    this->rodzajDichromatyzmu = rodzajDichromatyzmu;
}

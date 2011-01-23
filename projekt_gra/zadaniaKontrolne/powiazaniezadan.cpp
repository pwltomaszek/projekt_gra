#include "powiazaniezadan.h"
#include "zadaniekontrolne.h"
#include "QDebug"

PowiazanieZadan::PowiazanieZadan()
{
}

//void PowiazanieZadan::powiazZadania(std::vector<ZadanieKontrolne *> zadaniaPowiazane){
//    this->zadaniaPowiazane = zadaniaPowiazane;

//    for( unsigned int i = 0; i < zadaniaPowiazane.size(); ++i )
//        zadaniaPowiazane.at( i )->kontenerPowiazania = this;
//}


void PowiazanieZadan::powiazZadania(){
    for( unsigned int i = 0; i < zadaniaPowiazane.size(); ++i )
        zadaniaPowiazane.at( i )->kontenerPowiazania = this;
}


void PowiazanieZadan::ustawSprawdzanieKolizji( bool r ){
    foreach(ZadanieKontrolne* el, zadaniaPowiazane)
        el->sprawdzajKolizje = r;
}

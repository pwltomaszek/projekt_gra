#ifndef PUNKTKONTROLNY_H
#define PUNKTKONTROLNY_H

#include "zadaniekontrolne.h"

class PunktKontrolny : Przeszkoda
{
public:
    PunktKontrolny();
    void dzialanie( const Pojazd *pojazd );

};




#endif // PUNKTKONTROLNY_H

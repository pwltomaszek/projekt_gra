#include "pojazd.h"
#include "przeszkoda.h"

Przeszkoda::Przeszkoda(float rx, float ry, float rz, float dx, float dy)
{
    this->przesuniecieX = dx;
    this->przesuniecieY = dy;

    this->rozmiarX = rx;
    this->rozmiarY = ry;
    this->rozmiarZ = rz;
}

bool Przeszkoda::koliduje(const Pojazd *pojazd)
{
    dzialanie(pojazd);

    return boost::geometry::intersects( this->obszarKolizji, pojazd->obszarKolizji );
}

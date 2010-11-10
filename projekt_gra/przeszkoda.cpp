#include "przeszkoda.h"

Przeszkoda::Przeszkoda(float dx, float dy)
{
    this->dx = dx;
    this->dy = dy;
}

bool Przeszkoda::koliduje(const Pojazd &pojazd)
{
    dzialanie(pojazd);

    return boost::geometry::intersects( this->obszarKolizji, pojazd.obszarKolizji );
}

#include "przeszkoda.h"

bool Przeszkoda::koliduje(const Przeszkoda &przeszkoda)
{
    return boost::geometry::intersects( this->poly, przeszkoda.poly );
}

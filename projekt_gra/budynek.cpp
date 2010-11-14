#include <QDebug>

#include "budynek.h"

#include "opengl/mesh.h"
#include "opengl/opengl.h"

Budynek::Budynek(uint szer, uint dl, uint wys, float dx, float dy)
    : Przeszkoda( szer, dl, wys, dx, dy )
{
    this->mMesh = Node::node( "Budynek" );
}

void Budynek::przeliczObszarKolizji(uint x, uint y)
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

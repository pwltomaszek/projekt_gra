#include <QDebug>

#include "budynek.h"

#include "opengl/mesh.h"
#include "opengl/opengl.h"

Node* Budynek::mesh;

Budynek::Budynek()
{
}

Budynek::Budynek(uint szer, uint dl, float dx, float dy)
    : Przeszkoda( dx, dy )
{
    this->szer = szer;
    this->dl = dl;
}

void Budynek::rysuj(uint i, uint j)
{
    for( uint a = 0; a < dx; ++a ) {
        for( uint b = 0; b < dy; ++b ) {
            Przeszkoda::rysuj( i + a, j + b );

            mesh->draw();

            GLWrapper::instance().popMatrix();
        }
    }
}

void Budynek::przeliczObszarKolizji(float x, float y)
{
    float coords[ 5 ][ 2 ] = { { 0.0, 0.0 },
                               { (float)szer, 0.0 },
                               { (float)szer, (float)dl },
                               { 0.0, (float)dl },
                               { 0.0, 0.0 } };
    for( int i = 0; i < 5; ++i ) {
        coords[ i ][ 0 ] += x + dx;
        coords[ i ][ 1 ] += y + dy;
    }

    assign( obszarKolizji, coords );
    correct( obszarKolizji );
}

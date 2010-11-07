#include <QDebug>

#include "budynek.h"

#include "opengl/mesh.h"
#include "opengl/opengl.h"

Node* Budynek::mesh;

Budynek::Budynek()
{
}

Budynek::Budynek( int dx, int dy, int x, int y )
{
    this->dx = dx;
    this->dy = dy;
    this->y = y;
    this->x = x;
    //this->przeliczObszarKolizji();
}

void Budynek::rysuj(uint i, uint j)
{
    for( uint a = 0; a < dx; ++a ) {
        for( uint b = 0; b < dy; ++b ) {
            ObiektNaMapie::rysuj( i + a, j + b );

            mesh->draw();

            GLWrapper::instance().popMatrix();
        }
    }
}

void Budynek::przeliczObszarKolizji()
{
    float coords[ 5 ][ 2 ] = { { 0.0, 0.0 },
                               { (float)dx, 0.0 },
                               { (float)dx, (float)dy },
                               { 0.0, (float)dy },
                               { 0.0, 0.0 } };
    for( int i = 0; i < 5; ++i ) {
        coords[ i ][ 0 ] += x;
        coords[ i ][ 1 ] += y;
    }

    assign( poly, coords );
    correct( poly );
}

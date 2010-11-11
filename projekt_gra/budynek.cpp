#include <QDebug>

#include "budynek.h"

#include "opengl/mesh.h"
#include "opengl/opengl.h"

Node* Budynek::mesh;

Budynek::Budynek(uint szer, uint dl, float dx, float dy)
    : Przeszkoda( szer, dl, 0, dx, dy )
{
}

void Budynek::rysuj()
{
    GLWrapper &gl = GLWrapper::instance();

    for( uint a = 0; a < rozmiarX; ++a )
        for( uint b = 0; b < rozmiarY; ++b ) {
            gl.pushMatrix();
            gl.translate( glm::vec3( a, b, 0.f ) );

            mesh->draw();

            gl.popMatrix();
        }
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

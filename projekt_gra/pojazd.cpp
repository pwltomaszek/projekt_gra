#include <QDebug>

#include <algorithm>

#include "pojazd.h"

#include "opengl/glmadapter.h"
#include "opengl/node.h"
#include "opengl/opengl.h"

Pojazd::Pojazd()
{
    kat = 0.f;
}

void Pojazd::rysuj()
{
    GLWrapper &gl = GLWrapper::instance();

    gl.pushMatrix();
    gl.multMatrix( polozenie );

    mesh->draw();

    gl.popMatrix();
}

void Pojazd::przeliczObszarKolizji()
{
    glm::vec2 punkty[] = { glm::vec2( 0.3, 0.3 ),
                           glm::vec2( -0.3, 0.3 ),
                           glm::vec2( -0.3, -0.3 ),
                           glm::vec2( 0.3, -0.3 ) };

    for( int i = 0; i < 4; ++i ) {
        punkty[ i ] = glm::rotate( punkty[ i ], kat );
        punkty[ i ][ 0 ] += polozenie[ 3 ][ 0 ];
        punkty[ i ][ 1 ] += polozenie[ 3 ][ 1 ];
    }

    float coords[ 5 ][ 2 ];
    for( int i = 0; i < 5; ++i ) {
        coords[ i ][ 0 ] = punkty[ i % 4 ][ 0 ] / 2;
        coords[ i ][ 1 ] = punkty[ i % 4 ][ 1 ] / 2;
    }

    assign( poly, coords );
    correct( poly );
}

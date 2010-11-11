#include "droga.h"

#include "opengl/mesh.h"
#include "opengl/opengl.h"

Node* Droga::mesh;

Droga::Droga(Kierunek kierunek, float rx, float ry)
    : Przeszkoda( rx, ry )
{
    this->kierunek = kierunek;
}

void Droga::rysuj()
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

#include "chodnik.h"

#include "opengl/mesh.h"
#include "opengl/opengl.h"

Node* Chodnik::mesh;

Chodnik::Chodnik(float rx, float ry)
    : Przeszkoda( rx, ry )
{
}

void Chodnik::rysuj()
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

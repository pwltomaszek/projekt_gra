#include "obiektnamapie.h"

#include "opengl/opengl.h"

ObiektNaMapie::ObiektNaMapie()
{
}

void ObiektNaMapie::rysuj(uint i, uint j)
{
    GLWrapper &gl = GLWrapper::instance();

    gl.pushMatrix();
    gl.translate( glm::vec3( i * 2, j * 2, 0.f ) );
}

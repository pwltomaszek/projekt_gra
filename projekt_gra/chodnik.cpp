#include "chodnik.h"

#include "opengl/mesh.h"
#include "opengl/opengl.h"

Node* Chodnik::mesh;

Chodnik::Chodnik()
{
}

void Chodnik::rysuj(uint i, uint j)
{
    ObiektNaMapie::rysuj( i, j );

    mesh->draw();

    GLWrapper::instance().popMatrix();
}

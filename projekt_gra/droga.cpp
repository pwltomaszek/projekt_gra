#include "droga.h"

#include "opengl/mesh.h"
#include "opengl/opengl.h"

Node* Droga::mesh;

Droga::Droga()
{
}
Droga::Droga( Kierunek kierunek )
{
    this->kierunek = kierunek;
}

void Droga::rysuj(uint i, uint j)
{
    ObiektNaMapie::rysuj( i, j );

    mesh->draw();

    GLWrapper::instance().popMatrix();
}

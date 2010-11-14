#include "droga.h"

#include "opengl/mesh.h"
#include "opengl/node.h"
#include "opengl/opengl.h"

Droga::Droga(Kierunek kierunek, float rx, float ry)
    : Przeszkoda( rx, ry )
{
    this->kierunek = kierunek;

    this->mMesh = Node::node( "Droga" );
}

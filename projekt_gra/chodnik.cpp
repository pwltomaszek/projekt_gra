#include "chodnik.h"

#include "opengl/mesh.h"
#include "opengl/opengl.h"

Chodnik::Chodnik(float rx, float ry)
    : Przeszkoda( rx, ry )
{
    this->mMesh = Node::node( "Chodnik" );
}

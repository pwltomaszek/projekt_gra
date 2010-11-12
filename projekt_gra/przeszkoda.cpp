#include <algorithm>

#include "opengl/mesh.h"

#include "pojazd.h"
#include "przeszkoda.h"

bool Przeszkoda::rysujObszKolizji = true;

using namespace std;

Przeszkoda::Przeszkoda(float rx, float ry, float rz, float dx, float dy)
    : obszarKolizjiMesh( 0 )
{
    this->przesuniecieX = dx;
    this->przesuniecieY = dy;

    this->rozmiarX = rx;
    this->rozmiarY = ry;
    this->rozmiarZ = rz;
}

bool Przeszkoda::koliduje(const Pojazd *pojazd)
{
    dzialanie(pojazd);

    return boost::geometry::intersects( this->obszarKolizji, pojazd->obszarKolizji );
}

void Przeszkoda::stworzMeshKolizji()
{
    delete obszarKolizjiMesh;

    obszarKolizjiMesh = new Mesh( "" );
    vector< boost::geometry::point_2d > points = obszarKolizji.outer();
    obszarKolizjiMesh->mDataCount = points.size();
    obszarKolizjiMesh->mData[ Mesh::Vertex ] = new float[ obszarKolizjiMesh->mDataCount * 3 ];
    for( uint i = 0; i < obszarKolizjiMesh->mDataCount; ++i ) {
        obszarKolizjiMesh->mData[ Mesh::Vertex ][ i * 3 + 0 ] = points.at( i ).x();
        obszarKolizjiMesh->mData[ Mesh::Vertex ][ i * 3 + 1 ] = points.at( i ).y();
        obszarKolizjiMesh->mData[ Mesh::Vertex ][ i * 3 + 2 ] = 5.f;
    }
    obszarKolizjiMesh->shaderProgramType = GLWrapper::TextureShader;
}

void Przeszkoda::rysujObszarKolizji()
{
    if( !rysujObszKolizji )
        return;

    GLWrapper &gl = GLWrapper::instance();
    gl.draw( obszarKolizjiMesh );
}

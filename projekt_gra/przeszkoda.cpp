#include <algorithm>

#include "opengl/mesh.h"

#include "pojazd.h"
#include "przeszkoda.h"

bool Przeszkoda::rysujObszKolizji = true;

using namespace std;

Przeszkoda::Przeszkoda(float rx, float ry, float rz, float dx, float dy)
    : obszarKolizjiMesh( 0 ),
      mMesh( 0 )
{
    this->przesuniecieX = dx;
    this->przesuniecieY = dy;

    this->rozmiarX = rx;
    this->rozmiarY = ry;
    this->rozmiarZ = rz;

    koliduje = false;
}

bool Przeszkoda::czyKolidujeZPojazdem(const Pojazd *pojazd)
{
    bool tmp =  boost::geometry::intersects( this->obszarKolizji, pojazd->obszarKolizji );
    koliduje = tmp;
    dzialanie(pojazd);

    return tmp;
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

void Przeszkoda::rysuj()
{
    if( !mMesh )
        return;

    GLWrapper &gl = GLWrapper::instance();

    gl.pushMatrix();
    gl.scale( rozmiarX, rozmiarY, rozmiarZ );

    mMesh->draw();

    gl.popMatrix();
}

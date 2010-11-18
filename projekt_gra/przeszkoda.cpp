#include <QDebug>

#include <algorithm>

#include "opengl/mesh.h"

#include "pojazd.h"
#include "przeszkoda.h"

#include <boost/geometry/geometries/segment.hpp>

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

std::map< Przeszkoda::Krawedz, Przeszkoda::Krawedz > Przeszkoda::kolidujaceKrawedzie(const Pojazd *pojazd)
{
    /*
     * jesli nie bedzie sprawdzania czy pojazd i geometria nie koliduja ze soba jako
     * calosc przed wywolaniem ten funkcji, ze zwgledu na wydajnosc, nalezy odkomentowac
     * dwie ponizsze linie
     */
//    if( !boost::geometry::intersects( this->obszarKolizji, pojazd->obszarKolizji ) )
//        return

    std::map< Krawedz, Krawedz > krawedzie;

    float epsilon = 0.1;
    float maxX, minX, maxY, minY;
    // nie czytac 2 ponizszych linijek...
    maxX = maxY = -9999999;
    minX = minY = (uint)-1; //wystarczy, i tak zaczynamy w (0,0)

    vector< boost::geometry::point_2d > points = obszarKolizji.outer();
    for( uint i = 0; i < points.size(); ++i ) {
        boost::geometry::point_2d point = points.at( i );
        maxX = point.x() > maxX ? point.x() : maxX;
        maxY = point.y() > maxY ? point.y() : maxY;
        minX = point.x() < minX ? point.x() : minX;
        minY = point.y() < minY ? point.y() : minY;
    }

    for( uint i = 0; i < points.size(); ++i ) {
        uint ii = ( i + 1 ) % points.size();
        boost::geometry::point_2d p1 = points.at( i );
        boost::geometry::point_2d p2 = points.at( ii );
        double coords[ 3 ][ 2 ] = { { p1.x(), p1.y() },
                                    { p2.x(), p2.y() },
                                    { p2.x(), p2.y() } };
        boost::geometry::polygon_2d odcinek;
        assign( odcinek, coords );
        correct( odcinek );

        if( boost::geometry::intersects( odcinek, pojazd->obszarKolizji ) ) {
            if( fabs( p1.x() - p2.x() ) < epsilon ) {           // linia pionowa
                float pojazdX = pojazd->polozenieXY().x();

                bool scianaZachod = fabs( p1.x() - minX ) < epsilon;
                bool kierunekZachod = pojazdX < p1.x();
                krawedzie.insert( pair< Krawedz, Krawedz >( scianaZachod ? ZACHOD : WSCHOD,
                                                            kierunekZachod ? ZACHOD : WSCHOD ) );

            } else if( fabs( p1.y() - p2.y() ) < epsilon ) {    // linia pozioma
                float pojazdY = pojazd->polozenieXY().y();

                bool scianaPoludnie = fabs( p1.y() - minY ) < epsilon;
                bool kierunekPoludnie = pojazdY < p1.y();
                krawedzie.insert( pair< Krawedz, Krawedz >( scianaPoludnie ? POLUDNIE : POLNOC,
                                                            kierunekPoludnie ? POLUDNIE : POLNOC ) );
            }
        }
    }

    return krawedzie;
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

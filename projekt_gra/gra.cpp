#include "gra.h"

#include "opengl/colladameshfactory.h"
#include "opengl/opengl.h"

#include "budynek.h"
#include "chodnik.h"
#include "droga.h"

Gra::Gra()
{
    for( int i = 0; i < 256; ++i )
        mKlawisze[ i ] = false;

    widokZGory = true;
    widokTwarz = false;

    mTimeDelta = (double)clock() / (double)CLOCKS_PER_SEC;

    {
        ColladaMeshFactory factory( 0, "budynek.dae" );
        Budynek::mesh = factory.getScene( "Budynek" );
        Budynek::mesh->calculateTransformMatrix();
    }

    {
        ColladaMeshFactory factory( 0, "chodnik.dae" );
        Chodnik::mesh = factory.getScene( "Chodnik" );
        Chodnik::mesh->calculateTransformMatrix();
    }

    {
        ColladaMeshFactory factory( 0, "droga.dae" );
        Droga::mesh = factory.getScene( "Droga" );
        Droga::mesh->calculateTransformMatrix();
    }

    {
        ColladaMeshFactory factory( 0, "duck_triangulate.dae" );
        mPojazd.mesh = factory.getScene( "LOD3sp" );
        mPojazd.polozenie = glm::translate( glm::mat4( 1.f ), glm::vec3( 7, 5, 0.f ) );
        mPojazd.mesh->calculateTransformMatrix();
    }
}

void Gra::rysuj()
{
    GLWrapper &gl = GLWrapper::instance();

    gl.clear();
    gl.loadIdentity();

    if( widokTwarz ) {
        gl.rotate( 180.f, glm::vec3( 0.f, 1.f, 0.f ) );
        gl.translate( glm::vec3( 0.f, 0.3, 1.2 ) );
        gl.rotate( -1 * mPojazd.kat, glm::vec3( 0.f, 1.f, 0.f ) );
        gl.rotate( 180.f, glm::vec3( 0.f, 0.f, 1.f ) );
        gl.rotate( 90.f, glm::vec3( 1.f, 0.f, 0.f ) );
        gl.translate( glm::vec3( -mPojazd.polozenie[ 3 ][ 0 ],
                                             -mPojazd.polozenie[ 3 ][ 1 ],
                                              -1.f ) );
    } else if( widokZGory ) {
        gl.translate( glm::vec3( -mPojazd.polozenie[ 3 ][ 0 ],
                                 -mPojazd.polozenie[ 3 ][ 1 ],
                                 -7.f ) );
    } else {
        gl.rotate( -1 * mPojazd.kat, glm::vec3( 0.f, 1.f, 0.f ) );
        gl.rotate( 180.f, glm::vec3( 0.f, 0.f, 1.f ) );
        gl.rotate( 90.f, glm::vec3( 1.f, 0.f, 0.f ) );
        gl.translate( glm::vec3( -mPojazd.polozenie[ 3 ][ 0 ],
                                             -mPojazd.polozenie[ 3 ][ 1 ],
                                             -1.f ) );
    }

    mMapa.rysuj();
    mPojazd.rysuj();
}

void Gra::petla()
{
    mTimeDelta = (double)clock() / (double)CLOCKS_PER_SEC - mTimeDelta;

    przetworzKlawisze();
    przetworzLogikeGry();
}

void Gra::klawiszWcisniety(int klawisz, bool nacisniety)
{
    mKlawisze[ klawisz ] = nacisniety;
}

void Gra::przetworzKlawisze()
{
    float zmianaKata = 0;
    float dx, dy, dz;
    dx = dy = dz = 0;

    if( mKlawisze[ Qt::Key_Left ] )
        zmianaKata = 0.05;

    if( mKlawisze[ Qt::Key_Right ] )
        zmianaKata = -0.05;

    if( mKlawisze[ Qt::Key_Up ] )
        dy = -0.001;

    if( mKlawisze[ Qt::Key_Down ] )
        dy = 0.001;

    if( mKlawisze[ Qt::Key_Home ] )
        widokZGory = !widokZGory;

    if( mKlawisze[ Qt::Key_Home ] )
        widokZGory = false;

    zmianaKata *= mTimeDelta;
    dx *= mTimeDelta;
    dy *= mTimeDelta;
    dz *= mTimeDelta;

    glm::mat4 backup = mPojazd.polozenie;

    mPojazd.polozenie = glm::rotate( mPojazd.polozenie, zmianaKata, glm::vec3( 0.f, 0.f, 1.f ) );
    mPojazd.polozenie = glm::translate( mPojazd.polozenie, glm::vec3( dx, dy, dz ) );
    mPojazd.kat += zmianaKata;
    mPojazd.przeliczObszarKolizji();

    if( mMapa.zachodziKolizja( &mPojazd ) ) {
        mPojazd.polozenie = backup;
        mPojazd.kat -= zmianaKata;
    }
}

void Gra::przetworzLogikeGry()
{

}

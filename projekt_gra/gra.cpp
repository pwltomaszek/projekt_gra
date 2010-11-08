#include "gra.h"

#include "opengl/colladameshfactory.h"
#include "opengl/opengl.h"

#include "budynek.h"
#include "chodnik.h"
#include "droga.h"

#include <QGraphicsTextItem>

Gra::Gra()
{
    mTimer.start();

    akcje.insert( Qt::Key_Up, W_PRZOD );
    akcje.insert( Qt::Key_Left, SKRET_LEWO );
    akcje.insert( Qt::Key_Right, SKRET_PRAWO );
    akcje.insert( Qt::Key_Down, W_TYL  );
    akcje.insert( Qt::Key_Space, HAMOWANIE  );
    akcje.insert( Qt::Key_Home, ZMIANA_KAMERY  );

    mPojazd.stop();

    widok = Z_GORY;

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
        ColladaMeshFactory factory( 0, "camaro.dae" );
        factory.readFromFile( "camaro.mesh" );
        mPojazd.mesh = factory.getScene( "Camaro" );
        mPojazd.polozenie = glm::translate( mPojazd.polozenie, glm::vec3( 7, 5, 0.f ) );
        mPojazd.mesh->calculateTransformMatrix();
//        factory.writeToFile( "camaro.mesh", Mesh::mMeshes.at( "CamaroMesh" ) );
    }
}

void Gra::rysuj()
{
    GLWrapper &gl = GLWrapper::instance();

    gl.clear();
    gl.loadIdentity();

    switch( widok ){
        case PSYCHO:{
            gl.rotate( 180.f, glm::vec3( 0.f, 1.f, 0.f ) );
            gl.translate( glm::vec3( 0.f, 0.7, 1.2 ) );
            gl.rotate( -1 * mPojazd.kat, glm::vec3( 0.f, 1.f, 0.f ) );
            gl.rotate( 180.f, glm::vec3( 0.f, 0.f, 1.f ) );
            gl.rotate( 90.f, glm::vec3( 1.f, 0.f, 0.f ) );
            gl.translate( glm::vec3( -mPojazd.polozenie[ 3 ][ 0 ],
                                     -mPojazd.polozenie[ 3 ][ 1 ],
                                     -1.f ) );
            break;
        }
        case Z_GORY:{
            gl.translate( glm::vec3( -mPojazd.polozenie[ 3 ][ 0 ],
                                     -mPojazd.polozenie[ 3 ][ 1 ],
                                     -7.f ) );
            break;
        }
        case FPP:{
            gl.rotate( -1 * mPojazd.kat, glm::vec3( 0.f, 1.f, 0.f ) );
            gl.rotate( 180.f, glm::vec3( 0.f, 0.f, 1.f ) );
            gl.rotate( 90.f, glm::vec3( 1.f, 0.f, 0.f ) );
            gl.translate( glm::vec3( -mPojazd.polozenie[ 3 ][ 0 ],
                                                 -mPojazd.polozenie[ 3 ][ 1 ],
                                                 -1.f ) );
        }
    }

    mMapa.rysuj();
    mPojazd.rysuj();
}

void Gra::petla()
{
    double currentTime = (double)mTimer.elapsed() / 1000.0;
    mTimeDelta = currentTime - mCurrentTime;
    mCurrentTime = currentTime;

    przetworzLogikeGry();
    przesunGracza();
}

void Gra::klawiszWcisniety(int klawisz){

    Akcje a = akcje[ klawisz ];

    switch ( a ) {
        case SKRET_LEWO:
            mPojazd.skretLewo( true );
            break;

        case SKRET_PRAWO:
             mPojazd.skretPrawo( true );
            break;

        case W_PRZOD:
            mPojazd.doPrzodu( true );
            break;

        case W_TYL:
            mPojazd.doTylu( true );
            break;

        case HAMOWANIE:
            mPojazd.hamowanie( true );
            break;

        case ZMIANA_KAMERY:
            widok = widoki(widok+1);
            if(widok == KONIEC)
                widok = widoki(0);
            break;

        default:
            return;
    }
}

void Gra::klawiszZwolniony(int klawisz){

    Akcje a = akcje[ klawisz ];

    switch ( a ) {
        case SKRET_LEWO:
            mPojazd.skretLewo( false );
            break;

        case SKRET_PRAWO:
             mPojazd.skretPrawo( false );
            break;

        case W_PRZOD:
            mPojazd.doPrzodu( false );
            break;

        case W_TYL:
            mPojazd.doTylu( false );
            break;

        case HAMOWANIE:
            mPojazd.hamowanie( false );
            break;

        default:
            return;
    }
}

void Gra::przetworzLogikeGry(){

}

void Gra::przesunGracza(){
    glm::mat4 backup = mPojazd.polozenie;

    mPojazd.mTimeDelta = mTimeDelta;

    mPojazd.przeliczObszarKolizji();

    if( mMapa.zachodziKolizja( &mPojazd ) ) {
        mPojazd.cofnijPoKolizji( backup );
    }
}

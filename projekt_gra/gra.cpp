#include "gra.h"

#include "opengl/colladameshfactory.h"
#include "opengl/material.h"
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
    akcje.insert( Qt::Key_End, PODSWIETLENIE_OBSZ_KOLIZJI );

    mPojazd.stop();

    //Przeszkoda::rysujObszKolizji = !Przeszkoda::rysujObszKolizji;
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
        mPojazd.polozenie = glm::translate( mPojazd.polozenie, glm::vec3( 0, 10, 0.f ) );
        mPojazd.mesh->calculateTransformMatrix();

        m2.mesh = factory.getScene( "Camaro" );
        m2.polozenie = glm::translate( m2.polozenie, glm::vec3( 4, 10, 0.f ) );
        m2.mesh->calculateTransformMatrix();

        m7.mesh = factory.getScene( "Camaro" );
        m7.polozenie = glm::translate( m7.polozenie, glm::vec3( 30, 10, 0.f ) );
        m7.mesh->calculateTransformMatrix();

        m6.mesh = factory.getScene( "Camaro" );
        m6.polozenie = glm::translate( m6.polozenie, glm::vec3( 25, 10, 0.f ) );
        m6.mesh->calculateTransformMatrix();

        m5.mesh = factory.getScene( "Camaro" );
        m5.polozenie = glm::translate( m5.polozenie, glm::vec3( 20, 10, 0.f ) );
        m5.mesh->calculateTransformMatrix();

        m4.mesh = factory.getScene( "Camaro" );
        m4.polozenie = glm::translate( m4.polozenie, glm::vec3( 15, 10, 0.f ) );
        m4.mesh->calculateTransformMatrix();

        m3.mesh = factory.getScene( "Camaro" );
        m3.polozenie = glm::translate( m3.polozenie, glm::vec3( 10, 10, 0.f ) );
        m3.mesh->calculateTransformMatrix();

//        factory.writeToFile( "camaro.mesh", Mesh::mMeshes.at( "CamaroMesh" ) );
    }

    // niech ten kod tu trochê powisi, mo¿e przydaæ siê do rysowania przezroczystych obszarow
//    Material *obszarKolizjiMat = new Material;
//    float czerwony[] = { 1, 0, 0, 0.5 };
//    obszarKolizjiMat->ambient = new float[ 4 ];
//    memcpy( obszarKolizjiMat->ambient, czerwony, 4 * sizeof( float ) );
//    obszarKolizjiMat->diffuse = new float[ 4 ];
//    memcpy( obszarKolizjiMat->diffuse, czerwony, 4 * sizeof( float ) );

//    Mesh::addMaterial( "czerwienAlpha", obszarKolizjiMat );
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
                                     -50.f ) );
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
//    m2.rysuj();
//    m3.rysuj();
//    m4.rysuj();
//    m5.rysuj();
//    m6.rysuj();
//    m7.rysuj();

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

        case PODSWIETLENIE_OBSZ_KOLIZJI:
            Przeszkoda::rysujObszKolizji = !Przeszkoda::rysujObszKolizji;

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

    if( mMapa.zachodziKolizjaFizyczna( &mPojazd ) ) {
        mPojazd.cofnijPoKolizji( backup );
    }

    if( mMapa.zachodziKolizjaZZadaniem( &mPojazd ) ){
        //to cos
    }
}

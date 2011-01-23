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
    widok = FPP;

    {
        ColladaMeshFactory factory( 0, "budynek.dae" );
        Node* node = factory.getScene( "Budynek" );
        node->calculateTransformMatrix();
        Node::addNode( "Budynek", node );
    }

    {
        ColladaMeshFactory factory( 0, "znaki/stop.dae" );
        Node* node = factory.getScene( "scena" );
        node->calculateTransformMatrix();
        Node::addNode( "Znak", node );
    }

    {
        ColladaMeshFactory factory( 0, "chodnik.dae" );
        Node* node = factory.getScene( "Chodnik" );
        node->calculateTransformMatrix();
        Node::addNode( "Chodnik", node );
    }

    {
        ColladaMeshFactory factory( 0, "droga.dae" );
        Node* node = factory.getScene( "Droga" );
        node->calculateTransformMatrix();
        Node::addNode( "Droga", node );
    }

    {
        ColladaMeshFactory factory( 0, "sam.dae" );
        Node* node = factory.getScene( "scena" );
//        factory.readFromFile( "camaro.mesh" );
        mPojazd.mMesh = node;
        Node::addNode( "Samochod", node );
    }

//    {
//        ColladaMeshFactory factory( 0, "camaro.dae" );
//        factory.readFromFile( "camaro.mesh" );
//        mPojazd.mMesh = factory.getScene( "Camaro" );
//        mPojazd.polozenie = glm::translate( mPojazd.polozenie, glm::vec3( 0, 15, 0.f ) );
//        mPojazd.mMesh->calculateTransformMatrix();

////        factory.writeToFile( "camaro.mesh", Mesh::mMeshes.at( "CamaroMesh" ) );
//    }

    {
        ColladaMeshFactory factory( 0, "sam.dae" );
//        factory.readFromFile( "camaro.mesh" );
        mPojazd.mMesh = factory.getScene( "scena" );
        mPojazd.polozenie = glm::translate( mPojazd.polozenie, glm::vec3( 0, 15, 0.f ) );
        mPojazd.mMesh->calculateTransformMatrix();

//        factory.writeToFile( "camaro.mesh", Mesh::mMeshes.at( "CamaroMesh" ) );
    }

    // mapê nale¿y tworzyæ po wczytaniu wszystkich meshy
    mMapa = new Mapa;
}

Gra::~Gra()
{
    delete mMapa;
}

void Gra::rysuj()
{
    GLWrapper &gl = GLWrapper::instance();

    gl.clear();
    gl.loadIdentity();

    switch( widok ){
//        case PSYCHO:{
//            gl.rotate( 180.f, glm::vec3( 0.f, 1.f, 0.f ) );
//            gl.translate( glm::vec3( 0.f, 0.7, 1.2 ) );
//            gl.rotate( -1 * mPojazd.kat, glm::vec3( 0.f, 1.f, 0.f ) );
//            gl.rotate( 180.f, glm::vec3( 0.f, 0.f, 1.f ) );
//            gl.rotate( 90.f, glm::vec3( 1.f, 0.f, 0.f ) );
//            gl.translate( glm::vec3( -mPojazd.polozenie[ 3 ][ 0 ],
//                                     -mPojazd.polozenie[ 3 ][ 1 ],
//                                     -1.f ) );
//            break;
//        }
        case Z_GORY:{
            gl.translate( glm::vec3( -mPojazd.polozenie[ 3 ][ 0 ],
                                     -mPojazd.polozenie[ 3 ][ 1 ],
                                     -40.f ) );
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

    glm::vec4 lightPos( 0, 1000, 1000, 1 );
    lightPos = gl.mModelViewMatrix * lightPos;

    delete gl.light;
    gl.light = new LightSource( lightPos.x, lightPos.y, lightPos.z,
                             0.9, 0.9, 0.9,
                             0.8, 0.8, 0.8 );

    mMapa->rysuj();
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

    if( mMapa->zachodziKolizjaFizyczna( &mPojazd ) ) {
        mPojazd.cofnijPoKolizji( backup );
    }

    if( mMapa->zachodziKolizjaZZadaniem( &mPojazd ) ){
        //to cos
    }
}

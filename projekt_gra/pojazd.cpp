#include <QDebug>

#include <algorithm>

#include "pojazd.h"

#include "opengl/glmadapter.h"
#include "opengl/node.h"
#include "opengl/opengl.h"
#include <math.h>

#define MAX_PREDKOSC            10
//#define MAX_KAT                 180
//TODO: najlepiej by przyspieszenie nie bylo stale, a zalezne od aktualnej predkosci, skretu, etc.
#define PRZYSPIESZENIE          0.005

Pojazd::Pojazd()
{
    kat = 0.f;
    predkosc = 0;
}

void Pojazd::rysuj()
{
    GLWrapper &gl = GLWrapper::instance();

    gl.pushMatrix();
    gl.multMatrix( polozenie );

    mesh->draw();

    gl.popMatrix();
}

//TODO: not important
//  rozbudowac klase pojazd o realistyczny model danych: osie, waga, zakres skretu osi, etc.
//  do zaimplementowania odpowiedniej fizyki jazdy, tj. skretu,
//  przyspieszania, swobodnego zwalniania, hamowania, poslizgu, przyczepnosci.
//  moze sie przydac superklasa do tworzenia modeli roznych pojazdow AI

void Pojazd::ruchSwobodny(){
    if( wPrzod || wTyl || zahamowanie )
        return;

    int znak = 1; //+ lub - okreslaja ruch pojazdu w przod, tyl
    if ( predkosc < 0 ) znak = -1;
    predkosc = fabs(predkosc);
    predkosc -= PRZYSPIESZENIE*0.7;

    predkosc *= znak;
    dy += predkosc;
}

void Pojazd::przeliczObszarKolizji()
{    
//    qDebug()<<"predkosc km/h: " << predkosc*6;

    zmianaKata = 0;
    dx = dy = dz = 0;

    if( skretL )
        zmianaKata = 100 ;

    if( skretP )
        zmianaKata = -100;

    if( zahamowanie ){
        int znak = 1;
        if ( predkosc < 0 ) znak = -1;
        predkosc = fabs(predkosc);
        predkosc -= PRZYSPIESZENIE*6;

        predkosc *= znak;
        dy += predkosc;
    }else if( wPrzod ){
        if( predkosc <0 )
            predkosc += PRZYSPIESZENIE;
        predkosc += PRZYSPIESZENIE*3;
        dy += predkosc;
        if ( dy >= MAX_PREDKOSC )
            dy = MAX_PREDKOSC;
    }else if( wTyl ){
        if( predkosc >0 )
            predkosc -= PRZYSPIESZENIE;
        predkosc -= PRZYSPIESZENIE*3;
        dy += predkosc;
        if ( dy <= -MAX_PREDKOSC/5 )
            dy = -MAX_PREDKOSC/5;
    }

    if( predkosc < 0.1 )  //dla cofania
        zmianaKata *= -1;

    ruchSwobodny();

    predkosc = dy;

    zmianaKata *= mTimeDelta;
    dx *= mTimeDelta;
    dy *= mTimeDelta;
    dz *= mTimeDelta;

    polozenie = glm::rotate( polozenie, zmianaKata, glm::vec3( 0.f, 0.f, 1.f ) );
    polozenie = glm::translate( polozenie, glm::vec3( dx, -dy, dz ) );
    kat += zmianaKata;


    glm::vec2 punkty[] = { glm::vec2( 0.3, 0.3 ),
                           glm::vec2( -0.3, 0.3 ),
                           glm::vec2( -0.3, -0.3 ),
                           glm::vec2( 0.3, -0.3 ) };

    for( int i = 0; i < 4; ++i ) {
        punkty[ i ] = glm::rotate( punkty[ i ], kat );
        punkty[ i ][ 0 ] += polozenie[ 3 ][ 0 ];
        punkty[ i ][ 1 ] += polozenie[ 3 ][ 1 ];
    }

    float coords[ 5 ][ 2 ];
    for( int i = 0; i < 5; ++i ) {
        coords[ i ][ 0 ] = punkty[ i % 4 ][ 0 ] / 2;
        coords[ i ][ 1 ] = punkty[ i % 4 ][ 1 ] / 2;
    }

    assign( poly, coords );
    correct( poly );
}

void Pojazd::stop( ){
    skretLewo( false );
    skretPrawo( false );
    doPrzodu( false );
    doTylu( false );
    dy = dx = dz = 0;
    predkosc = 0;
}

void Pojazd::cofnijPoKolizji( glm::mat4 polozenie ){
    stop();
    this->polozenie = polozenie;
    kat -= zmianaKata * mTimeDelta;
}

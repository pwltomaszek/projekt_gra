#ifndef POJAZD_H
#define POJAZD_H

#include "opengl/glmadapter.h"

#include "przeszkoda.h"

class Node;

class Pojazd : public Przeszkoda
{
public:
    Pojazd();

    void stop( bool r);
    void skretLewo( bool r ) { skretL = r; }
    void skretPrawo( bool r ) { skretP = r; }
    void doPrzodu( bool r ) { wPrzod = r; }
    void doTylu( bool r ) { wTyl = r; }
    void hamowanie( bool r ) { zahamowanie = r; }

    void cofnijPoKolizji( glm::mat4 polozenie );

    void przeliczObszarKolizji();
    glm::mat4 polozenie;
    void rysuj();

    float kat;
    double mTimeDelta;


    Node *mesh;

private:
    float dy, dx, dz;
    float zmianaKata;
    float predkosc;

    //zmienia atrybuty predkosci i przesuniecia bez uwzgledniania akcji od kierowcy,
    //czyli jazda 'na luzie'
    void ruchSwobodny();

    bool skretL, skretP, wPrzod, wTyl, zahamowanie;
};

#endif // POJAZD_H

#ifndef POJAZD_H
#define POJAZD_H

#include "../gl4fun/glmadapter.h"

#include "przeszkoda.h"

class Node;

class Pojazd : public Przeszkoda
{
public:
    Pojazd();

    void przeliczObszarKolizji();
    glm::mat4 polozenie;
    float kat;

    void rysuj();

    Node *mesh;
};

#endif // POJAZD_H

#ifndef DESSIN_H
#define DESSIN_H

#include "all.h"

extern maison maisons[NB_MAISONS];
extern arbre arbres[NB_ARBRES];

extern animal animaux[NB_ANIMAUX];


extern bonhomme bonhommes[NB_BONHOMMES];


extern rect carte;

void dessinerCarreX(int x, int y1, int y2, int z1, int z2);

void dessinerCarreY(int x1, int x2, int y, int z1, int z2);

void dessinerCarreZ(int x1, int x2, int y1, int y2, int z);

void dessinerCarre(point p1, point p2, point p3, point p4);

void dessiner();

void dessinerCarte();

void dessinerMaisons();

void dessinerArbres();

void dessinerBonhommes();

void dessinerAnimaux();

#endif

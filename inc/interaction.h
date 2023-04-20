#ifndef INTERACTION_H
#define INTERACTION_H

#include <math.h>
#include "all.h"

extern maison maisons[NB_MAISONS];
extern arbre arbres[NB_ARBRES];
extern animal animaux[NB_ANIMAUX];
extern bonhomme bonhommes[NB_BONHOMMES];
extern rect carte;
extern bonhomme joueur;

void jouerBonhommes();

void jouerAnimaux();

int py(int x, int y);

int lePlusProche(int id, int type);

int estAutorise(int id, int x, int y);

void deplacer(int id, int type);

void modifierDirection(int id, int type);

void deplacerAlea(int id, int type);

void fuir(int id1, int id2);

void attraper(int id1, int id2);

#endif

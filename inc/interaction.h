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
extern double vitesse;
extern point direction;
extern int action;
extern int envol;
extern int debugMode;
extern int gaucheInput, droiteInput, avantInput, arriereInput, hautInput, basInput;

int estEnVie(int id, int type);

void jouerBonhommes();

void jouerAnimaux();

void jouerJoueur();

double py(double x, double y);

int lePlusProche(int id, int type);

void printCollision(int id1, type t1, int id2, type t2);

void separateHitboxes(point *pos1, rect *hb1, point *pos2, rect *hb2);

int collision(int id1, double x, double y, type t1, int id2, type t2);

int estAutorise(int id, double x, double y, int type);

void deplacer(int id, int type);

void modifierDirection(int id, int type);

void deplacerAlea(int id, int type);

void fuir(int id1, int id2);

void attraper(int id1, int id2);

void tuer(int id);

#endif

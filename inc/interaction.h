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

int estEnVie(int id, int type);

void jouerBonhommes();

void jouerAnimaux();

double py(double x, double y);

int lePlusProche(int id, int type);

int intersectionMaison(int id, double x, double y, int type);

int intersectionArbre(int id, double x, double y, int type);

int intersectionBonhomme(int id, double x, double y, int type);

int intersectionAnimal(int id, double x, double y, int type);

int collision(int id1, type t1, int id2, type t2);

void verifieToutesCollisions();

int estAutorise(int id, double x, double y, int type);

void deplacer(int id, int type);

void modifierDirection(int id, int type);

void deplacerAlea(int id, int type);

void fuir(int id1, int id2);

void attraper(int id1, int id2);

void tuer(int id);

#endif

#ifndef INIT_H
#define INIT_H

#include "all.h"

extern maison maisons[NB_MAISONS];
extern arbre arbres[NB_ARBRES];
extern animal animaux[NB_ANIMAUX];
extern bonhomme bonhommes[NB_BONHOMMES];
extern bonhomme joueur;
extern rect carte;
extern double vitesse;

void init();
void initCarte();
void initMaison();
void initArbre();
void initBonhomme();
void initAnimal();
void initJoueur(int x, int y, int z);

#endif

#ifndef INTERACTION_H
#define INTERACTION_H

#include "all.h"


extern maison maisons[NB_MAISONS];
extern arbre arbres[NB_ARBRES];
extern animal animaux[NB_ANIMAUX];
extern bonhomme bonhommes[NB_BONHOMMES];
extern rect carte;


void init();
void initCarte();
void initMaisons();
void initArbres();
void initBonhommes();
void initAnimaux();

#endif

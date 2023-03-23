#ifndef INTERACTION_H
#define INTERACTION_H

#include "all.h"


extern maison maisons[NB_MAISONS];
extern arbre arbres[NB_ARBRES];
extern animal animaux[NB_ANIMAUX];
extern bonhomme bonhommes[NB_BONHOMMES];
extern rect carte;

extern point posMaisons[NB_MAISONS];
extern point posArbres[NB_ARBRES];
extern point posAnimaux[NB_ANIMAUX];
extern point posBonhommes[NB_BONHOMMES];

void init();
void initCarte();
void initMaisons();
void initArbres();
void initBonhommes();
void initAnimaux();

#endif

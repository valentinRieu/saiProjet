#ifndef INTERACTION_H
#define INTERACTION_H

#include "common.h"
#include "struct.h"
#define NB_MAISONS 64
#define NB_ARBRES 64
#define NB_ANIMAUX 64
#define NB_BONHOMMES 64

#define HAUTEUR_CARTE 300
#define LONGUEUR_CARTE 1000
#define LARGEUR_CARTE 1000



extern maison maisons[NB_MAISONS];
extern arbre arbres[NB_ARBRES];

extern animal animaux[NB_ANIMAUX];


extern bonhomme bonhommes[NB_BONHOMMES];


extern rect carte;


#endif

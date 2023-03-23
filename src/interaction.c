#include "interaction.h"

maison maisons[NB_MAISONS];
arbre arbres[NB_ARBRES];

animal animaux[NB_ANIMAUX];


bonhomme bonhommes[NB_BONHOMMES];

rect carte;

void init(){
	srand(time(NULL));
	initCarte();
    initMaisons();
    initArbres();
    initBonhommes();
    initAnimaux();
}

position newRandomPosition(){
	int rand;
    position p;
    p.p = (point){100, 100, 100};
    p.direction = (point){1,1,0};
    return p;
}

void initCarte(){
	carte = (rect){HAUTEUR_CARTE, LARGEUR_CARTE, LONGUEUR_CARTE};
}
void initMaisons(){
    int i;
    
    for(i=0;i<NB_MAISONS;i++){
        maisons[i].id = i;
        maisons[i].p = newRandomPosition();
        maisons[i].batiment = (rect){20, 20, 20};
        maisons[i].hauteurToit = 20;
        maisons[i].couleurMur = (couleur){1,1,1};
        maisons[i].couleurToit = (couleur){1,1,1};
    }
}

void initArbres(){
    int i;
    
    for(i=0;i<NB_ARBRES;i++){
        arbres[i].id = i;
        arbres[i].p = newRandomPosition();
        arbres[i].tronc = (cylindre){5,15};
        arbres[i].tete = (boule){10};
    }
}

void initBonhommes(){
    int i;
    
    for(i=0;i<NB_BONHOMMES;i++){
        bonhommes[i].id = i;
        bonhommes[i].p = newRandomPosition();
		bonhommes[i].corps = (rect){5, 4, 4};
        bonhommes[i].pieds = (cylindre){2,5};
		bonhommes[i].bras = (cylindre){2,5};
        bonhommes[i].tete = (boule){5};
        bonhommes[i].hitbox = (rect){12,6,6};
    }
}

void initAnimaux(){
    int i;
    
    for(i=0;i<NB_ANIMAUX;i++){
        animaux[i].id = i;
        animaux[i].p = newRandomPosition();
		animaux[i].corps = (rect){2,4,4};
        animaux[i].pattes = (cylindre){2,1};
        animaux[i].tete = (boule){4};
        animaux[i].hitbox = (rect){6,10,4};
    }
}
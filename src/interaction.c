#include "interaction.h"

maison maisons[NB_MAISONS];
arbre arbres[NB_ARBRES];

animal animaux[NB_ANIMAUX];


bonhomme bonhommes[NB_BONHOMMES];

rect carte;
void initMaisons();
void init(){
    initMaisons();
    initArbres();
    initBonhommes();
    initAnimals();
}

position newRandomPosition(){
    position p;
    p.p = (point){100, 100, 100};
    p.direction = (point){1,1,0};
    return p;
}

void initMaisons(){
    int i;
    
    for(i=0;i<NB_MAISONS;i++){
        maisons[i].id = i;
        maisons[i].p = newRandomPosition();
        maisons[i].batiment = (rect){20, 20, 20};
        maisons[i].hauteurToit = 10;
        maisons[i].couleurMur = (couleur){1,1,1};
        maisons[i].couleurToit = (couleur){1,1,1};
    }
}

void initArbres(){
    int i;
    
    for(i=0;i<NB_ARBRES;i++){
        arbres[i].id = i;
        arbres[i].p = newRandomPosition();
        arbres[i].tronc = (cylindre){(point){20, 20, 20},20,0};
        arbres[i].tete = (boule){(point){20, 20, 20},20};
        arbres[i].hitbox = (rect){20,20,20};
    }
}

void initBonhommes(){
    int i;
    
    for(i=0;i<NB_BONHOMMES;i++){
        bonhommes[i].id = i;
        bonhommes[i].p = newRandomPosition();
        bonhommes[i].pieds[1] = (cylindre){(point){20, 20, 20},20,0};
        bonhommes[i].pieds[2] = (cylindre){(point){20, 20, 20},20,0};
        bonhommes[i].bras[1] = (cylindre){(point){20, 20, 20},20,0};
        bonhommes[i].pieds[2] = (cylindre){(point){20, 20, 20},20,0};
        bonhommes[i].tete = (boule){(point){20, 20, 20},20};
        bonhommes[i].hitbox = (rect){20,20,20};
    }
}

void initAnimaux(){

}
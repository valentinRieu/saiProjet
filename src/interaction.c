#include "interaction.h"

void init(){
    int i, j, i1=0,i2=0,i3=0,i4=0;
    int rx=50, ry=50;
	
	carte = (rect){HAUTEUR_CARTE, LARGEUR_CARTE, LONGUEUR_CARTE};
	
    for(i=0;i<NB_MAISONS+NB_ARBRES+NB_ANIMAUX+NB_BONHOMMES;i++){
		j=rand()%4;
		switch(j){
			case 0:
				if(i1>=NB_MAISONS){
					if(i2!<NB_ARBRES){
						j=1;
					}else if(i3<NB_ANIMAUX){
						j=2;
					}else{
						j=3;
					}
				}
			break;
			case 1:
				if(i2>=NB_ARBRES){
					if(i1<NB_MAISONS){
						j=0;
					}else if(i3<NB_ANIMAUX){
						j=2;
					}else{
						j=3;
					}
				}
			break;
			case 2:
				if(i3>=NB_ANIMAUX){
					if(i1<NB_MAISONS){
						j=0;
					}else if(i2<NB_ARBRES){
						j=1;
					}else{
						j=3;
					}
				}
			break;
			default:
				if(i4>=NB_BONHOMMES){
					if(i1<NB_MAISONS){
						j=0;
					}else if(i2<NB_ARBRES){
						j=1;
					}else{
						j=2;
					}
				}
		}
		switch(j){
			case 0:
				initMaison(rx, ry, i1);
				i1++;
			break;
			case 1:
				initArbre(rx, ry, i2);
				i2++;
			break;
			case 2:
				initAnimal(rx, ry, i3);
				i3++;
			break;
			default:
				initBonhomme(rx, ry, i4);
				i4++;
		}
		
		rx+=40+rand()%41;
		if(rx>950){
			rx=50;
			ry+=40+rand()%41;
		}
    }
}

void initMaison(int x, int y, int i){
        maisons[i].id = i;
        maisons[i].p = (point){x, y, 0};
        maisons[i].batiment = (rect){20, 20, 20};
        maisons[i].hauteurToit = 20;
        maisons[i].couleurMur = (couleur){1,1,1};
        maisons[i].couleurToit = (couleur){1,1,1};
	posMaisons[i] = (point){(x, y, 0)};
}
		
void initArbre(int x, int y, int i){
        arbres[i].id = i;
        arbres[i].p = (point){x, y, 0};
        arbres[i].tronc = (cylindre){5,15};
        arbres[i].tete = (boule){10};
		posArbres[i] = (point){(x, y, 0)};
}

void initBonhomme(int x, int y, int i){
        bonhommes[i].id = i;
        bonhommes[i].p = (point){x, y, 0};
		bonhommes[i].corps = (rect){5, 4, 4};
        bonhommes[i].pieds = (cylindre){2,5};
		bonhommes[i].bras = (cylindre){2,5};
        bonhommes[i].tete = (boule){5};
        bonhommes[i].hitbox = (rect){12,6,6};
		posBonhommes[i] = (point){(x, y, 0)};
}

void initAnimal(int x, int y, int i){
        animaux[i].id = i;
        animaux[i].p = (point){x, y, 0};
		animaux[i].corps = (rect){2,4,4};
        animaux[i].pattes = (cylindre){2,1};
        animaux[i].tete = (boule){4};
        animaux[i].hitbox = (rect){6,10,4};
		posAnimaux[i] = (point){(x, y, 0)};
}
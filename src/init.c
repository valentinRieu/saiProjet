#include "init.h"

void init(){
    int i, j, i1=0,i2=0,i3=0,i4=0;
    int rx=50, ry=50;
	
    carte = (rect){LARGEUR_CARTE, LONGUEUR_CARTE};
	
    for(i=0;i<NB_MAISONS+NB_ARBRES+NB_ANIMAUX+NB_BONHOMMES;i++){
        j=rand()%4;
        switch(j){
        case 0:
            if(i1>=NB_MAISONS){
                if(i2<NB_ARBRES){
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
    maisons[i].pos = (point){x, y, 0};
    maisons[i].hitBox = (rect){40, 40};
}
		
void initArbre(int x, int y, int i){
    arbres[i].pos = (point){x, y, 0};
    arbres[i].hitBox = (rect){20, 20};
}

void initBonhomme(int x, int y, int i){
    bonhommes[i].enVie = 1;
    bonhommes[i].isDepl = 0;
    bonhommes[i].pos = (point){x, y, 0};
    bonhommes[i].direction = (point){10, 0, 5};
    bonhommes[i].hitBox = (rect){10,10};
}

void initAnimal(int x, int y, int i){
    animaux[i].enVie = 1;
    animaux[i].isDepl = 0;
    animaux[i].pos = (point){x, y, 0};
    animaux[i].direction = (point){10,0,5};
    animaux[i].hitBox = (rect){10,5};
}
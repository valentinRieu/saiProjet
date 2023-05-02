#include "interaction.h"

int estEnVie(int id, int type){
    if(id == -1){//joueur
        return joueur.enVie;
    }
    if(type == 0){//bonhomme
        return bonhommes[id].enVie;
    }
    //animal
    return animaux[id].enVie;
}

void jouerBonhommes(){
    int i, j;

    for(i=0;i<NB_BONHOMMES;i++){
        if(!estEnVie(i, 0))
            continue;

        j = lePlusProche(i, 0);//id
        //fuir j
        if(j==-1){
            deplacerAlea(i, 0);
        }else{
            fuir(i, j);
        }
    }
}

void jouerAnimaux(){
    int i, j;

    for(i=0;i<NB_ANIMAUX;i++){
        if(!estEnVie(i, 1))
            continue;

        j = lePlusProche(i, 1);//id
        //aller vers j
        if(j==-1){
            deplacerAlea(i, 1);
        }else{
            attraper(i, j);
        }
    }
}

//théorème de pythagore pour les surfaces
double py(double x, double y){
    return x*x+y*y;
}

int lePlusProche(int id, int type){
    int i, id2=0;
    double min, d;
    point p, p2;

    if(type==0){
        p = bonhommes[id].pos;
        min=py(p.x-animaux[0].pos.x, p.y-animaux[0].pos.y);
        for(i=1;i<NB_ANIMAUX;i++){
            p2 = animaux[id].pos;
            if((d=py(p.x-p2.x, p.y-p2.y))<min){
                min = d;
                id2 = i;
            }
        }
    }else{
        p = animaux[id].pos;
        min=py(p.x-joueur.pos.x, p.y-joueur.pos.y);
        for(i=0;i<NB_BONHOMMES;i++){
            p2 = bonhommes[id].pos;
            if((d=py(p.x-p2.x, p.y-p2.y))<min){
                min = d;
                id2 = i;
            }
        }
    }
    if(min>20)
        return -1;
    return id2;
}

int intersectionMaison(int id, double x, double y, int type){
    int i;
	
    if(id == -1){
	for(i=0;i<NB_MAISONS;i++){
            if(1)
                return 1;
	}
    }else if(type == 0){
		
    }else{
		
    }
	
    return 0;
}

int intersectionArbre(int id, double x, double y, int type){
	
    return 0;
}

int intersectionBonhomme(int id, double x, double y, int type){
	
    return 0;
}

int intersectionAnimal(int id, double x, double y, int type){
	
    return 0;
}

int estAutorise(int id, double x, double y, int type){
    int id2;
	
    /*if(intersectionMaison(id, x, y, type) || intersectionArbre(id, x, y, type)){
        return 0;
    }
    if(type == 0){//bonhomme
        if(intersectionBonhomme(id, x, y, type)){
            return 0;
        }
        if(intersectionAnimal(id, x, y, type)){
            tuer(id);
            return 0;
        }
    }else{//animal
        if((id2 = intersectionBonhomme(id, x, y, type))){
            tuer(id2);
            return 0;
        }
        if(intersectionAnimal(id, x, y, type)){
            return 0;
        }
        }*/
    return 1;
}

void deplacer(int id, int type){
    double i, j;

    if(type == 0){
        i = bonhommes[id].pos.x+bonhommes[id].direction.x;
        j = bonhommes[id].pos.y+bonhommes[id].direction.y;
        if(estAutorise(id,i,j,0)){
            bonhommes[id].pos.x = i;
            bonhommes[id].pos.y = j;
            if(i-bonhommes[id].cible.x < vitesse && i-bonhommes[id].cible.x > -vitesse && j-bonhommes[id].cible.y < vitesse && j-bonhommes[id].cible.y > -vitesse){
                bonhommes[id].isDepl = 0;
            }

        }else{
            bonhommes[id].isDepl = 0;
        }

    }else{
        i = animaux[id].pos.x+animaux[id].direction.x;
        j = animaux[id].pos.y+animaux[id].direction.y;
        if(estAutorise(id,i,j,1)){
            animaux[id].pos.x = i;
            animaux[id].pos.y = j;
            if(i-animaux[id].cible.x < vitesse && i-animaux[id].cible.x > -vitesse && j-animaux[id].cible.y < vitesse && j-animaux[id].cible.y > -vitesse){
                animaux[id].isDepl = 0;
            }
        } else{
            animaux[id].isDepl = 0;
        }
    }
}

void modifierDirection(int id, int type){
    double x = rand()%400;
    double y = rand()%400;
    double dx, dy, d;

    if(type == 0){//modif direction
        dx = x-bonhommes[id].pos.x;
        dy = y-bonhommes[id].pos.y;
        d = sqrt(py(dx, dy));
        /*k = sqrt(py(x-bonhommes[id].pos.x,y-bonhommes[id].pos.y))/10;
          dx = bonhommes[id].pos.x+k*(x-bonhommes[id].pos.x);
          dy = bonhommes[id].pos.y+k*(y-bonhommes[id].pos.y);*/
        bonhommes[id].direction.x = vitesse*dx/d;
        bonhommes[id].direction.y = vitesse*dy/d;
        bonhommes[id].cible.x = x;
        bonhommes[id].cible.y = y;
        bonhommes[id].isDepl = 1;
    }else{
        dx = x-bonhommes[id].pos.x;
        dy = y-bonhommes[id].pos.y;
        d = sqrt(py(dx, dy));
        /*k = sqrt(py(x-animaux[id].pos.x,y-animaux[id].pos.y))/10;
          dx = animaux[id].pos.x+k*(x-animaux[id].pos.x);
          dy = animaux[id].pos.y+k*(y-animaux[id].pos.y);*/
        animaux[id].direction.x = vitesse*dx/d;
        animaux[id].direction.y = vitesse*dy/d;
        animaux[id].cible.x = x;
        animaux[id].cible.y = y;
        animaux[id].isDepl = 1;
    }
}

void deplacerAlea(int id, int type){
    if(type == 0 && bonhommes[id].isDepl == 0){
        modifierDirection(id, type);
    }else if(animaux[id].isDepl == 0){
        modifierDirection(id, type);
    }
    deplacer(id, type);
}

void fuir(int id1, int id2){
    double x, y, dx, dy, d;

    dx = bonhommes[id1].pos.x-animaux[id2].pos.x;
    dy = bonhommes[id1].pos.y-animaux[id2].pos.y;
    d = sqrt(py(dx, dy));
    x = bonhommes[id1].pos.x-vitesse*dx/d;
    y = bonhommes[id1].pos.y-vitesse*dy/d;
    if(estAutorise(id1, x, y, 0)){
        bonhommes[id1].pos.x = x;
        bonhommes[id1].pos.y = y;
    }
}

void attraper(int id1, int id2){
    double x, y, dx, dy, d;

    dx = animaux[id1].pos.x-bonhommes[id2].pos.x;
    dy = animaux[id1].pos.y-bonhommes[id2].pos.y;
    d = sqrt(py(dx, dy));
    x = animaux[id1].pos.x+vitesse*dx/d;
    y = animaux[id1].pos.y+vitesse*dy/d;
    //il faut vérifier ici si l'animal a attrapé le bonhomme
    if(estAutorise(id1, x, y, 1)){
        animaux[id1].pos.x = x;
        animaux[id1].pos.y = y;
    }
}

void tuer(int id){
    if(id == -1)
        joueur.enVie = 0;
    else
        bonhommes[id].enVie = 0;
}
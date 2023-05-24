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

/* int intersectionMaison(int id, double x, double y, int type) { */
/*     printf("not used %d %f %f %d", id, x, y, type); */
/*     return 1; */
/* } */
/* int intersectionArbre(int id, double x, double y, int type) { */
/*     printf("not used %d %f %f %d", id, x, y, type); */
/*     return 1; */
/* } */
/* int intersectionBonhomme(int id, double x, double y, int type){ */
/*     printf("not used %d %f %f %d", id, x, y, type); */
/*     return 1; */
/* } */
/* int intersectionAnimal(int id, double x, double y, int type) { */
/*     printf("not used %d %f %f %d", id, x, y, type); */
/*     return 1; */
/* } */

int collision(int id1, type t1, int id2, type t2) {

    point *pos1, *pos2;
    rect *hb1, *hb2;

    switch(t1) {
    case JOUEUR:
        pos1 = &joueur.pos;
        hb1 = &joueur.hitBox;
        break;
    case BONHOMME:
        pos1 = &bonhommes[id1].pos;
        hb1 = &bonhommes[id1].hitBox;
        break;
    case ANIMAL:
        pos1 = &animaux[id1].pos;
        hb1 = &animaux[id1].hitBox;
        break;
    case ARBRE:
        pos1 = &arbres[id1].pos;
        hb1 = &arbres[id1].hitBox;
        break;
    case MAISON:
        pos1 = &maisons[id1].pos;
        hb1 = &maisons[id1].hitBox;
        break;
    }
    switch(t2) {
    case JOUEUR:
        pos2 = &joueur.pos;
        hb2 = &joueur.hitBox;
        break;
    case BONHOMME:
        pos2 = &bonhommes[id2].pos;
        hb2 = &bonhommes[id2].hitBox;
        break;
    case ANIMAL:
        pos2 = &animaux[id2].pos;
        hb2 = &animaux[id2].hitBox;
        break;
    case ARBRE:
        pos2 = &arbres[id2].pos;
        hb2 = &arbres[id2].hitBox;
        break;
    case MAISON:
        pos2 = &maisons[id2].pos;
        hb2 = &maisons[id2].hitBox;
        break;
    }

    // test de collision. test de z inutile en l'état

    rect hbdiv1 = (rect){(hb1->longueur / 2), (hb1->largeur / 2)};
    rect hbdiv2 = (rect){(hb2->longueur / 2), (hb2->largeur / 2)};


    point mint1 = (point){
        pos1->x - hbdiv1.longueur,
        pos1->y - hbdiv1.largeur,
        pos1->z};

    point maxt1 = (point){
        pos1->x + hbdiv1.longueur,
        pos1->y + hbdiv1.largeur,
        pos1->z};


    point mint2 = (point){
        pos2->x - hbdiv2.longueur,
        pos2->y - hbdiv2.largeur,
        pos2->z};

    point maxt2 = (point){
        pos2->x + hbdiv2.longueur,
        pos2->y + hbdiv2.largeur,
        pos2->z};

    return (mint1.x <= maxt2.x &&
            maxt1.x >= mint2.x &&
            mint1.y <= maxt2.y &&
            maxt1.y >= mint2.y);
    /* return (fabs(pos1->x - pos2->x) * 2 < (hb1->longueur + hb2->longueur) && */
    /*         fabs(pos1->y - pos2->y) * 2 < (hb1->largeur + hb2->largeur)); */
}


// fonction non optimale : méthode divide and conquer serait optimale

void printCollision(int id1, type t1, int id2, type t2) {

    char typ1[16], typ2[16];

    /* switch(t1) { */
    /* case JOUEUR: */
    /*     strcpy(typ1, "joueur"); */
    /*     break; */
    /* case BONHOMME: */
    /*     strcpy(typ1, "bonhomme"); */
    /*     break; */
    /* case ANIMAL: */
    /*     strcpy(typ1, "animal"); */
    /*     break; */
    /* case ARBRE: */
    /*     strcpy(typ1, "arbre"); */
    /*     break; */
    /* case MAISON: */
    /*     strcpy(typ1, "maison"); */
    /*     break; */
    /* } */
    if(t1 != JOUEUR) return;

    switch(t2) {
    case JOUEUR:
        strcpy(typ2, "joueur");
        break;
    case BONHOMME:
        strcpy(typ2, "bonhomme");
        break;
    case ANIMAL:
        strcpy(typ2, "animal");
        break;
    case ARBRE:
        strcpy(typ2, "arbre");
        break;
    case MAISON:
        strcpy(typ2, "maison");
        break;

    default:
        strcpy(typ2, "wtf");
        break;
    }


    printf("collision entre entité de type joueur d'id %d, et entité de type %s d'id %d\n\n",
           id1, typ2, id2);
}

void verifieToutesCollisions() {
    // Vérification des collisions entre le joueur et les autres entités

    for(int i = 0; i < NB_BONHOMMES; i++) {
        if(collision(0, JOUEUR, i, BONHOMME)) {
            printCollision(0, JOUEUR, i, BONHOMME);
            joueur.pos = joueur.previousPos;
        }
    }
    for(int i = 0; i < NB_ANIMAUX; i++) {
        if(collision(0, JOUEUR, i, ANIMAL)) {
            printCollision(0, JOUEUR, i, ANIMAL);
            joueur.pos = joueur.previousPos;
        }
    }
    for(int i = 0; i < NB_ARBRES; i++) {
        if(collision(0, JOUEUR, i, ARBRE)) {
            printCollision(0, JOUEUR, i, ARBRE);
            joueur.pos = joueur.previousPos;
        }
    }
    for(int i = 0; i < NB_MAISONS; i++) {
        if(collision(0, JOUEUR, i, MAISON)) {
            printCollision(0, JOUEUR, i, MAISON);
            joueur.pos = joueur.previousPos;
        }
    }

    // Vérification des collisions entre les bonhommes et les autres entités
    for(int i = 0; i < NB_BONHOMMES; i++) {
        for(int j = 0; j < NB_ANIMAUX; j++) {
            if(collision(i, BONHOMME, j, ANIMAL)) {
                printCollision(i, BONHOMME, j, ANIMAL);
                bonhommes[i].pos = bonhommes[i].previousPos;
            }
        }
        for(int j = 0; j < NB_ARBRES; j++) {
            if(collision(i, BONHOMME, j, ARBRE)) {
                printCollision(i, BONHOMME, j, ARBRE);
                bonhommes[i].pos = bonhommes[i].previousPos;
            }
        }
        for(int j = 0; j < NB_MAISONS; j++) {
            if(collision(i, BONHOMME, j, MAISON)) {
                printCollision(i, BONHOMME, j, MAISON);
                bonhommes[i].pos = bonhommes[i].previousPos;
            }
        }
    }

    // Vérification des collisions entre les animaux et les autres entités
    for(int i = 0; i < NB_ANIMAUX; i++) {
        for(int j = 0; j < NB_ARBRES; j++) {
            if(collision(i, ANIMAL, j, ARBRE)) {
                printCollision(i, ANIMAL, j, ARBRE);
                animaux[i].pos = animaux[i].previousPos;
            }
        }
        for(int j = 0; j < NB_MAISONS; j++) {
            if(collision(i, ANIMAL, j, MAISON)) {
                printCollision(i, ANIMAL, j, MAISON);
                animaux[i].pos = animaux[i].previousPos;
            }
        }
    }


    // Les arbres et les maisons sont statiques, donc nous n'avons pas besoin de vérifier leurs collisions avec d'autres entités
}

int estAutorise(int id, double x, double y, int type) {
    return 1;
}

void deplacer(int id, int type){
    double i, j;

    if(type == 0){
        i = bonhommes[id].pos.x+bonhommes[id].direction.x;
        j = bonhommes[id].pos.y+bonhommes[id].direction.y;
        if(estAutorise(id,i,j,0)){
            // on sauvegarde la précédente position : utilisé si collision
            bonhommes[id].previousPos = bonhommes[id].pos;

            bonhommes[id].pos.x = i;
            bonhommes[id].pos.y = j;
            if(i-bonhommes[id].cible.x < vitesse && i-bonhommes[id].cible.x > -vitesse && j-bonhommes[id].cible.y < vitesse && j-bonhommes[id].cible.y > -vitesse){
                bonhommes[id].isDepl = 0;
            }

        }else{
            bonhommes[id].isDepl = 0;
        }

    }else{
        animaux[id].previousPos = animaux[id].pos;
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

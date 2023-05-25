#include "interaction.h"
int invincibilite = 0;
clock_t previousHit = 0;
clock_t testInvincibilite;
clock_t newHit;

//Permet de savoir si le joueur ou un bonhomme est en vie
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

//Permet de faire jouer les bonhommes
void jouerBonhommes(){
    int i, j;
    printf("bonhommes en jaune\n");
    for(i=0;i<NB_BONHOMMES;i++){
        if(!estEnVie(i, 0))
            continue;

        j = lePlusProche(i, 0);//id
        //fuir j
        if(j==-2){
            deplacerAlea(i, 0);
        }else{
            fuir(i, j);
        }
    }
}

//Permet de faire jouer les animaux
void jouerAnimaux(){
    int i, j;
    invincibilite = 0;
    printf("animaux en cyan\n");
    for(i=0;i<NB_ANIMAUX;i++){
        if(!estEnVie(i, 1))
            continue;

        j = lePlusProche(i, 1);//id
        //aller vers j
        if(j==-2){
            deplacerAlea(i, 1);
        }else{
            attraper(i, j);
        }
    }
}

//Permet de faire jouer le joueur
void jouerJoueur() {
    double x2, y2;
    double z2;
    x2 = joueur.pos.x;
    y2 = joueur.pos.y;
    z2 = joueur.pos.z;
    if(!action){
        return;
    }

    joueur.previousPos = joueur.pos;
    if(avantInput){
        x2 += joueur.direction.x;
        y2 += joueur.direction.y;
    }

    if(arriereInput){
        x2 -= joueur.direction.x;
        y2 -= joueur.direction.y;
    }

    if(gaucheInput){
        x2 += direction.x;
        y2 += direction.y;
    }

    if(droiteInput){
        x2 -= direction.x;
        y2 -= direction.y;
    }
    if(envol){
        if(hautInput){
            z2 += 1;
        }

        if(basInput){
            z2 -= 1;
        }
    } else z2 = INITIAL_Z;
    if(estAutorise(-1, x2, y2, 0))
        joueur.pos = (point){x2, y2, z2};
}

//théorème de pythagore pour les surfaces
double py(double x, double y){
    return x*x+y*y;
}

//Trouve le bonhomme(l'animal) le plus proche d'un animal (bonhomme) d'id donné et renvoi sont id s'il est assez proche de l'animal(bonhomme)
int lePlusProche(int id, int type){
    int i, id2;
    double min, d;
    point p, p2;

    if(type==0){
        p = bonhommes[id].pos;
        min=py(p.x-animaux[0].pos.x, p.y-animaux[0].pos.y);
        id2 = 0;
        for(i=1;i<NB_ANIMAUX;i++){
            p2 = animaux[id].pos;
            if((d=py(p.x-p2.x, p.y-p2.y))<min){
                min = d;
                id2 = i;
            }
        }
    }else{
        p = animaux[id].pos;
        if(envol){
            min=py(p.x-bonhommes[0].pos.x, p.y-bonhommes[0].pos.y);
            id2 = 0;
        }else{
            min=py(p.x-joueur.pos.x, p.y-joueur.pos.y);
            id2 = -1;
        }
        for(i=0;i<NB_BONHOMMES;i++){
            p2 = bonhommes[id].pos;
            if((d=py(p.x-p2.x, p.y-p2.y))<min){
                min = d;
                id2 = i;
            }
        }

    }
    if(min>1000)
        return -2;
    return id2;
}

//Permet d'afficher les collisions sur le terminal en debugMode
void printCollision(int id1, type t1, int id2, type t2) {

    if(!debugMode)
        return;

    char typ1[16], typ2[16];

    switch(t1) {
    case JOUEUR:
        strcpy(typ1, "joueur");
        break;
    case BONHOMME:
        strcpy(typ1, "bonhomme");
        break;
    case ANIMAL:
        strcpy(typ1, "animal");
        break;
    case ARBRE:
        strcpy(typ1, "arbre");
        break;
    case MAISON:
        strcpy(typ1, "maison");
        break;
    }

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

//Permet de déplacer des éléments si leurs hitbox sont confondues
void separateHitboxes(point *pos1, rect *hb1, point *pos2, rect *hb2) {

    // Step 2: Calculate collision direction
    int dx = pos1->x - pos2->x;
    int dy = pos1->y - pos2->y;

    // Step 3: Determine minimum translation distance
    int halfWidth1 = hb1->largeur;
    int halfWidth2 = hb2->largeur;
    int halfLength1 = hb1->longueur;
    int halfLength2 = hb2->longueur;

    int minSeparationX = halfWidth1 + halfWidth2 - abs(dx);
    int minSeparationY = halfLength1 + halfLength2 - abs(dy);

    int separationX = (minSeparationX > 0) ? minSeparationX : 0;
    int separationY = (minSeparationY > 0) ? minSeparationY : 0;

    // Step 4: Move hitboxes away from each other
    if (dx < 0) {
        pos1->x -= dx * 2;
        pos2->x += dx * 2;
    } else {
        pos1->x += dx * 2;
        pos2->x -= dx * 2;
    }

    if (dy < 0) {
        pos1->y -= dy * 2;
        pos2->y += dy * 2;
    } else {
        pos1->y += dy * 2;
        pos2->y -= dy * 2;
    }
}

//Permet de détecter une collision entre un élément d'id id1 et de type t1 qui veux se déplacer à la position (x,y) et un élément d'id id2 et de type t2
int collision(int id1, double x, double y, type t1, int id2, type t2) {

    point pos1 = (point){x, y, 0}, *pos2;
    rect *hb1, *hb2;

    switch(t1) {
    case JOUEUR:
        hb1 = &joueur.hitBox;
        break;
    case BONHOMME:
        hb1 = &bonhommes[id1].hitBox;
        break;
    case ANIMAL:
        hb1 = &animaux[id1].hitBox;
        break;
    case ARBRE:
        hb1 = &arbres[id1].hitBox;
        break;
    case MAISON:
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


    point mint1 = (point){
        pos1.x,
        pos1.y,
        pos1.z};

    point maxt1 = (point){
        pos1.x + hb1->longueur,
        pos1.y + hb1->largeur,
        pos1.z};


    point mint2 = (point){
        pos2->x,
        pos2->y,
        pos2->z};

    point maxt2 = (point){
        pos2->x + hb2->longueur,
        pos2->y + hb2->largeur,
        pos2->z};

    return (mint1.x <= maxt2.x &&
            maxt1.x >= mint2.x &&
            mint1.y <= maxt2.y &&
            maxt1.y >= mint2.y);
    /* return (fabs(pos1->x - pos2->x) * 2 < (hb1->longueur + hb2->longueur) && */
    /*         fabs(pos1->y - pos2->y) * 2 < (hb1->largeur + hb2->largeur)); */
}

//Test si l'élément d'id id et de type type peut se déplacer à la position (x,y)
int estAutorise(int id, double x, double y, int type) {

    int i;

    if(x<=5 || x>=LARGEUR_CARTE-5 || y<=5 || y>=LONGUEUR_CARTE-5)
        return 0;

    if(id == -1){
        for(i = 0; i < NB_BONHOMMES; i++) {
            if(estEnVie(i, 0) && collision(id, x, y, JOUEUR, i, BONHOMME)) {
                printCollision(0, JOUEUR, i, BONHOMME);
                return 0;
            }
        }

        for(i = 0; i < NB_ANIMAUX; i++) {
            if(estEnVie(i, 1) && collision(id, x, y, JOUEUR, i, ANIMAL)) {
                printCollision(0, JOUEUR, i, ANIMAL);
                if(!envol){
                    if(!invincibilite) {
                        printf("touché\n");
                        if(previousHit == 0) {
                            joueur.enVie--;
                            previousHit = clock();
                            invincibilite = 1;
                            separateHitboxes(&joueur.pos, &joueur.hitBox, &animaux[i].pos, &animaux[i].hitBox);

                            return 0;
                        }
                        newHit = clock();
                        if((double)(newHit - previousHit) / CLOCKS_PER_SEC  > 1) {
                            joueur.enVie--;
                            previousHit = clock();
                            invincibilite = 1;
                            separateHitboxes(&joueur.pos, &joueur.hitBox, &animaux[i].pos, &animaux[i].hitBox);

                            return 0;
                        }
                        return 0;
                    }
                    testInvincibilite = clock();
                    if((double)(testInvincibilite - previousHit) / CLOCKS_PER_SEC > 1) {
                        invincibilite = 0;
                    }
                    return 0;

                }
            }
        }

        for(i = 0; i < NB_ARBRES; i++) {
            if(collision(id, x, y, JOUEUR, i, ARBRE)) {
                printCollision(0, JOUEUR, i, ARBRE);
                return 0;
            }
        }

        for(i = 0; i < NB_MAISONS; i++) {
            if(collision(id, x, y, JOUEUR, i, MAISON)) {
                printCollision(0, JOUEUR, i, MAISON);
                return 0;
            }
        }

    }
    else if(type == 0){
        if(estEnVie(-1, 0) && collision(id, x, y, BONHOMME, 0, JOUEUR)){
            printCollision(id, BONHOMME, 0, JOUEUR);
            return 0;
        }

        for(i = 0; i < NB_BONHOMMES; i++) {
            if(i != id && estEnVie(i, 0) && collision(id, x, y, BONHOMME, i, BONHOMME)) {
                printCollision(id, BONHOMME, i, BONHOMME);
                return 0;
            }
        }

        for(i = 0; i < NB_ANIMAUX; i++) {
            if(estEnVie(i, 1) && collision(id, x, y, BONHOMME, i, ANIMAL)) {
                printCollision(id, BONHOMME, i, ANIMAL);
                tuer(i);
                return 0;
            }
        }

        for(i = 0; i < NB_ARBRES; i++) {
            if(collision(id, x, y, BONHOMME, i, ARBRE)) {
                printCollision(id, BONHOMME, i, ARBRE);
                return 0;
            }
        }

        for(i = 0; i < NB_MAISONS; i++) {
            if(collision(id, x, y, BONHOMME, i, MAISON)) {
                printCollision(id, BONHOMME, i, MAISON);
                return 0;
            }
        }

    } else {
        if(estEnVie(-1, 0) && collision(id, x, y, ANIMAL, 0, JOUEUR)){
            printCollision(0, ANIMAL, 0, JOUEUR);
            if(!envol)
                tuer(-1);
            return 0;
        }
        for(i = 0; i < NB_BONHOMMES; i++) {
            if(estEnVie(i, 0) && collision(id, x, y, ANIMAL, i, BONHOMME)) {
                printCollision(0, ANIMAL, i, BONHOMME);
                tuer(i);
            }
        }
        for(i = 0; i < NB_ANIMAUX; i++) {
            if(i != id && estEnVie(i, 1) && collision(id, x, y, ANIMAL, i, ANIMAL)) {
                printCollision(id, ANIMAL, i, ANIMAL);
                return 0;
            }
        }

        for(i = 0; i < NB_ARBRES; i++) {
            if(collision(id, x, y, ANIMAL, i, ARBRE)) {
                printCollision(id, ANIMAL, i, ARBRE);
                return 0;
            }
        }

        for(i = 0; i < NB_MAISONS; i++) {
            if(collision(id, x, y, ANIMAL, i, MAISON)) {
                printCollision(id, ANIMAL, i, MAISON);
                return 0;
            }
        }

    }

    return 1;
}
//Permet de déplacer un élément d'id id et de type type
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

//Permet de modifier la diretion vers laquelle se dirige un élément
void modifierDirection(int id, int type){
    double x = rand()%(LARGEUR_CARTE-10)+5;
    double y = rand()%(LONGUEUR_CARTE-10)+5;
    double dx, dy, d;

    if(type == 0){
        dx = x-bonhommes[id].pos.x;
        dy = y-bonhommes[id].pos.y;
        d = sqrt(py(dx, dy));
        bonhommes[id].direction.x = vitesse*dx/d;
        bonhommes[id].direction.y = vitesse*dy/d;
        bonhommes[id].cible.x = x;
        bonhommes[id].cible.y = y;
        bonhommes[id].isDepl = 1;
    }else{
        dx = x-bonhommes[id].pos.x;
        dy = y-bonhommes[id].pos.y;
        d = sqrt(py(dx, dy));
        animaux[id].direction.x = vitesse*dx/d;
        animaux[id].direction.y = vitesse*dy/d;
        animaux[id].cible.x = x;
        animaux[id].cible.y = y;
        animaux[id].isDepl = 1;
    }
}

//Permet de se déplacer vers une nouvelle position aléatoire
void deplacerAlea(int id, int type){
    if(type)
        printf("animal %d déplacement aléatoire\n", id);
    else
        printf("bonhomme %d déplacement aléatoire\n", id);

    if(type == 0 && bonhommes[id].isDepl == 0){
        modifierDirection(id, type);
    }else if(animaux[id].isDepl == 0){
        modifierDirection(id, type);
    }
    deplacer(id, type);
}

//Permet à un bonhomme de fuir un animal
void fuir(int id1, int id2){
    double x, y, dx, dy, d;

    if(debugMode)
        printf("bonhomme %d veut fuir animal %d\n", id1, id2);

    dx = bonhommes[id1].pos.x-animaux[id2].pos.x;
    dy = bonhommes[id1].pos.y-animaux[id2].pos.y;
    d = sqrt(py(dx, dy));
    x = bonhommes[id1].pos.x+vitesse*dx/d;
    y = bonhommes[id1].pos.y+vitesse*dy/d;
    if(estAutorise(id1, x, y, 0)){
        bonhommes[id1].pos.x = x;
        bonhommes[id1].pos.y = y;
        bonhommes[id1].isDepl = 0;
    }
}

//Permet à un animal d'attraper un bonhomme
void attraper(int id1, int id2){
    double x, y, dx, dy, d;

    if(debugMode)
        printf("animal %d veut attraper bonhomme %d\n", id1, id2);

    if(id2 == -1){
        dx = animaux[id1].pos.x-joueur.pos.x;
        dy = animaux[id1].pos.y-joueur.pos.y;
    }else{
        dx = animaux[id1].pos.x-bonhommes[id2].pos.x;
        dy = animaux[id1].pos.y-bonhommes[id2].pos.y;
    }
    d = sqrt(py(dx, dy));
    x = animaux[id1].pos.x-vitesse*dx/d;
    y = animaux[id1].pos.y-vitesse*dy/d;

    if(estAutorise(id1, x, y, 1)){
        animaux[id1].pos.x = x;
        animaux[id1].pos.y = y;
        animaux[id1].isDepl = 0;
    }
}

//Permet de tuer un bonhomme
void tuer(int id){
    if(id == -1)
        joueur.enVie--;
    else
        bonhommes[id].enVie = 0;
}

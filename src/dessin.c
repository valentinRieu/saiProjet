#include "dessin.h"

void dessinerCarreX(int x, int y1, int y2, int z1, int z2){
    glBegin(GL_QUADS);
    glVertex3f(x, y1, z1);
    glVertex3f(x, y1, z2);
    glVertex3f(x, y2, z2);
    glVertex3f(x, y2, z1);
    glEnd();
}

void dessinerCarreY(int x1, int x2, int y, int z1, int z2){
    glBegin(GL_QUADS);
    glVertex3f(x1, y, z1);
    glVertex3f(x1, y, z2);
    glVertex3f(x2, y, z2);
    glVertex3f(x2, y, z1);
    glEnd();
}

void dessinerCarreZ(int x1, int x2, int y1, int y2, int z){
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z);
    glVertex3f(x1, y2, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x2, y1, z);
    glEnd();
}

void dessinerCarre(point p1, point p2, point p3, point p4){
    glBegin(GL_QUADS);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glVertex3f(p4.x, p4.y, p4.z);
    glEnd();
}

void dessiner(){
    dessinerCarte();
    dessinerMaisons();
    dessinerArbres();
    dessinerBonhommes();
    dessinerAnimaux();
}

void dessinerCarte(){
    //dessin du sol
    glColor3f(0, 1, 0);
    dessinerCarreZ(0,LONGUEUR_CARTE,0,LARGEUR_CARTE,0);
	
    //dessin du ciel
    glColor3f(0, 0, 1);
    dessinerCarreZ(0,LONGUEUR_CARTE,0,LARGEUR_CARTE,HAUTEUR_CARTE);
	
    dessinerCarreX(0,0,LARGEUR_CARTE,0,HAUTEUR_CARTE);
    dessinerCarreX(LONGUEUR_CARTE,0,LARGEUR_CARTE,0,HAUTEUR_CARTE);
	
	
    dessinerCarreY(0,LONGUEUR_CARTE,0,0,HAUTEUR_CARTE);
    dessinerCarreY(0,LONGUEUR_CARTE,LARGEUR_CARTE,0,HAUTEUR_CARTE);
}

void dessinerMaisons(){
    int i;
    point p;
    for(i=0;i<NB_MAISONS;i++){
        p = maisons[i].pos;
        glColor3f(1, 1, 1);
        dessinerCarreX(p.x,p.y,p.y+40,0,30);
        dessinerCarreX(p.x+40,p.y,p.y+40,0,30);
        dessinerCarreY(p.x,p.x+40,p.y,0,30);
        dessinerCarreY(p.x,p.x+40,p.y+40,0,30);
        dessinerCarreZ(p.x,p.x+40,p.y,p.y+40,30);
    }
}

void dessinerArbres(){
    int i;
    point p;
    for(i=0;i<NB_ARBRES;i++){
        p = arbres[i].pos;
        glColor3f(1, 0, 0);//tronc
        dessinerCarreX(p.x+6,p.y+6,p.y+10,0,10);
        dessinerCarreX(p.x+10,p.y+6,p.y+10,0,10);
        dessinerCarreY(p.x+6,p.x+10,p.y+6,0,10);
        dessinerCarreY(p.x+6,p.x+10,p.y+10,0,10);
        glColor3f(0, 1, 0);//feuille
        dessinerCarreX(p.x,p.y,p.y+16,10,20);
        dessinerCarreX(p.x+16,p.y,p.y+16,10,20);
        dessinerCarreY(p.x,p.x+16,p.y,10,20);
        dessinerCarreY(p.x,p.x+16,p.y+16,10,20);
        dessinerCarreZ(p.x,p.x+16,p.y,p.y+16,10);
        dessinerCarreZ(p.x,p.x+16,p.y,p.y+16,20);
    }
}

void dessinerBonhommes(){
    int i;
    point p;
    for(i=0;i<NB_BONHOMMES;i++){
        p = bonhommes[i].pos;
		
    }
}

void dessinerAnimaux(){
    int i;
    point p;
    for(i=0;i<NB_ANIMAUX;i++){
        p = animaux[i].pos;
		
    }
}
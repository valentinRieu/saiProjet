#include <math.h>
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

//à partir du point p, on trace un vecteur v vers l'endroit où l'on veut créer un point. v est déterminé en fonction du vecteur directeur d de l'objet, de dx et dy qui correspondent à l'agrandissement en x et en y et z est la position en z
point calculRotation(point p, point d, int angle, float dx, float dy, int z){
    point v;
    v.x = p.x+dx*(d.x*cos(angle*3.14/180)-d.y*sin(angle*3.14/180));
    v.y = p.y+dy*(d.y*cos(angle*3.14/180)-d.x*sin(angle*3.14/180));
    v.z = z;
    return v;
}

void dessinerBonhommes(){
    int i;
    point p;
    glColor3f(1, 0, 0);
    for(i=0;i<NB_BONHOMMES;i++){
        p = bonhommes[i].pos;//position
        /*d = bonhommes[i].direction;//vecteur
          dessinerCarre(calculRotation(p, d, 60, 0.5, 0.5, 2),//bas
          calculRotation(p, d, 120, 0.5, 0.5, 2),
          calculRotation(p, d, 240, 0.5, 0.5, 2),
          calculRotation(p, d, 300, 0.5, 0.5, 2));
          dessinerCarre(calculRotation(p, d, 60, 0.5, 0.5, 8),//haut
          calculRotation(p, d, 120, 0.5, 0.5, 8),
          calculRotation(p, d, 240, 0.5, 0.5, 8),
          calculRotation(p, d, 300, 0.5, 0.5, 8));
          dessinerCarre(calculRotation(p, d, 60, 0.5, 0.5, 2),//gauche
          calculRotation(p, d, 120, 0.5, 0.5, 2),
          calculRotation(p, d, 120, 0.5, 0.5, 8),
          calculRotation(p, d, 60, 0.5, 0.5, 8));
          dessinerCarre(calculRotation(p, d, 240, 0.5, 0.5, 2),//droite
          calculRotation(p, d, 300, 0.5, 0.5, 2),
          calculRotation(p, d, 300, 0.5, 0.5, 8),
          calculRotation(p, d, 240, 0.5, 0.5, 8));
          dessinerCarre(calculRotation(p, d, 60, 0.5, 0.5, 2),//avant
          calculRotation(p, d, 300, 0.5, 0.5, 2),
          calculRotation(p, d, 300, 0.5, 0.5, 8),
          calculRotation(p, d, 60, 0.5, 0.5, 8));
          dessinerCarre(calculRotation(p, d, 240, 0.5, 0.5, 2),//arriere
          calculRotation(p, d, 120, 0.5, 0.5, 2),
          calculRotation(p, d, 120, 0.5, 0.5, 8),
          calculRotation(p, d, 240, 0.5, 0.5, 8));*/
        glColor3f(1, 1, 0);//tronc
        dessinerCarreX(p.x+6,p.y+6,p.y+10,4,8);
        dessinerCarreX(p.x+10,p.y+6,p.y+10,4,8);
        dessinerCarreY(p.x+6,p.x+10,p.y+6,4,8);
        dessinerCarreY(p.x+6,p.x+10,p.y+10,4,8);
        dessinerCarreZ(p.x+6,p.x+10,p.y+6,p.y+10,4);
        dessinerCarreZ(p.x+6,p.x+10,p.y+6,p.y+10,8);
    }
}

void dessinerAnimaux(){
    int i;
    point p;
    for(i=0;i<NB_ANIMAUX;i++){
        p = animaux[i].pos;
        glColor3f(0, 1, 1);//tronc
        dessinerCarreX(p.x+6,p.y+2,p.y+6,2,6);
        dessinerCarreX(p.x+10,p.y+2,p.y+6,2,6);
        dessinerCarreY(p.x+6,p.x+10,p.y+2,2,6);
        dessinerCarreY(p.x+6,p.x+10,p.y+6,2,6);
        dessinerCarreZ(p.x+6,p.x+10,p.y+2,p.y+6,2);
        dessinerCarreZ(p.x+6,p.x+10,p.y+2,p.y+6,6);
    }
}
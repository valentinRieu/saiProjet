#include "dessin.h"

void dessinerCarreX(int x, int y1, int y2, int z1, int z2){
    glVertex3f(x, y1, z1);
    glVertex3f(x, y1, z2);
    glVertex3f(x, y2, z2);
    glVertex3f(x, y2, z1);
}

void dessinerCarreY(int x1, int x2, int y, int z1, int z2){
    glVertex3f(x1, y, z1);
    glVertex3f(x1, y, z2);
    glVertex3f(x2, y, z2);
    glVertex3f(x2, y, z1);
}

void dessinerCarreZ(int x1, int x2, int y1, int y2, int z){
    glVertex3f(x1, y1, z);
    glVertex3f(x1, y2, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x2, y1, z);
}

void dessinerCarre(point p1, point p2, point p3, point p4){
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glVertex3f(p4.x, p4.y, p4.z);
}

void dessiner(){
    dessinerCarte();
    
}

void dessinerCarte(){
    glBegin(GL_QUADS);
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
    glEnd();
}

void dessinerMaisons(){
    int i;
    point p;
    rect r;
    for(i=0;i<NB_MAISONS;i++){
        p = maisons[i].p.p;
        r = maisons[i].batiment;
        glColor3f(maisons[i].couleurMur.r,maisons[i].couleurMur.g,maisons[i].couleurMur.b);
            
        dessinerCarreX(p.x,p.y,p.y+r.largeur,p.z,p.z+r.hauteur);
        dessinerCarreX(p.x+r.longueur,p.y,p.y+r.largeur,p.z,p.z+r.hauteur);
            
        dessinerCarreY(p.x,p.x+r.longueur,p.y,p.z,p.z+r.hauteur);
        dessinerCarreY(p.x,p.x+r.longueur,p.y+r.largeur,p.z,p.z+r.hauteur);
            
        glColor3f(maisons[i].couleurToit.r,maisons[i].couleurToit.g,maisons[i].couleurToit.b);
        dessinerCarre((point){p.x,p.y,p.z+r.hauteur},(point){p.x+r.longueur,p.y,p.z+r.hauteur},(point){p.x+r.longueur,p.y+r.largeur,p.z+r.hauteur+maisons[i].hauteurToit},(point){p.x,p.y+r.largeur,p.z+r.hauteur+maisons[i].hauteurToit});
    }
}

void dessinerArbres(){
	
}

void dessinerBonhommes(){
	
}

void dessinerAnimaux(){
	
}
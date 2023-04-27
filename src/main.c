#include <math.h>
#include "all.h"
#include "init.h"
#include "interaction.h"
#include "dessin.h"

maison maisons[NB_MAISONS];
arbre arbres[NB_ARBRES];
animal animaux[NB_ANIMAUX];
bonhomme bonhommes[NB_BONHOMMES];
rect carte;

double angle = 0;
bonhomme joueur;

int vueY=0;
int vueZ=0;
double angleY=0;
double angleZ=0;
clock_t chrono;



//permet de dessiner l'origine du repère
void origine(){
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(1000,0,0);
    glColor3f(0, 1, 0);
    glVertex3f(0,0,0);
    glVertex3f(0,1000,0);
    glColor3f(0, 0, 1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1000);
    glEnd();
}

void gagne(){
    printf("GAGNE\n");
    exit(0);
}

void perdu(){
    printf("PERDU\n");
    exit(0);
}

int dernier() { return 0;}

void jouer(){


    jouerBonhommes();
    jouerAnimaux();
    if(dernier())
        gagne();
    if(!joueur.enVie)
        perdu();

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5,5,-5,5,5,1500);
    gluLookAt(joueur.pos.x, joueur.pos.y, joueur.pos.z, joueur.pos.x+joueur.direction.x, joueur.pos.y+joueur.direction.y, joueur.pos.z+joueur.direction.z, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //origine();
    dessiner();

    glutSwapBuffers();
}

void GererSouris(int x, int y){

    if(x==500 && y==500){
        return;
    }
    if(x<TAILLE_ECRAN/2-10){
        angleY++;
        if(angleY>359) angleY=0;
    }else if(x>TAILLE_ECRAN/2+10){
        angleY--;
        if(angleY<0) angleY=359;
    }

    joueur.direction.x=(int)(10*cos(angleY*3.14/180));
    joueur.direction.y=(int)(10*sin(angleY*3.14/180));
    //vueY = x;
    if(y<TAILLE_ECRAN/2-10){
        angleZ++;
        if(angleZ>44) angleZ=44;
    }else if(y>TAILLE_ECRAN/2+10){
        angleZ--;
        if(angleZ<-44) angleZ=-44;
    }

    joueur.direction.z=(int)(10*sin(angleZ*3.14/180));

    if((clock() - chrono)>100){
        glutWarpPointer(500,500);
        chrono = clock();
    }
}

void GererClavier(unsigned char touche, int x, int y){
    int x2, y2;

    if(touche == 'z'){
        x2 = joueur.pos.x + joueur.direction.x;
        y2 = joueur.pos.y + joueur.direction.y;
    }else if(touche == 'd'){
        x2 = joueur.pos.x - joueur.direction.y;
        y2 = joueur.pos.y - joueur.direction.x;
    }else if(touche == 's'){
        x2 = joueur.pos.x - joueur.direction.x;
        y2 = joueur.pos.y - joueur.direction.y;
    }else if(touche == 'q'){
        x2 = joueur.pos.x + joueur.direction.y;
        y2 = joueur.pos.y + joueur.direction.x;
    }else if(touche == '&'){
        exit(0);
    }else return;

    if(estAutorise(-1, x2, y2, 0)){
        joueur.pos.x = x2;
        joueur.pos.y = y2;
    }
}

int main(int argc, char **argv) {

    chrono=clock();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(TAILLE_ECRAN, TAILLE_ECRAN);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Projet SAI");
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5,5,-5,5,20,1500);
    gluLookAt(500, 500,0, 0, 0, 0, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    //glutSetCursor(GLUT_CURSOR_NONE);
    init();
    joueur.enVie = 1;
    joueur.pos=(point){500,500,5};
    joueur.direction=(point){10,0,5};
    joueur.hitBox = (rect){10,10};

    glutIdleFunc(jouer);
    glutPassiveMotionFunc(GererSouris);
    glutKeyboardFunc(GererClavier);

    glutMainLoop();

    return 0;
}

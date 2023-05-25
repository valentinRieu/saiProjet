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
point direction;

double vitesse = 1;

double angle = 0;
bonhomme joueur;
int debugMode = 0;
int envol = 0;

int action = 0;
int gaucheInput = 0, droiteInput = 0, avantInput = 0, arriereInput = 0, hautInput = 0, basInput = 0;

//int vueY=0;
//int vueZ=0;


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

int dernier() {
    int i;
    for(i=0;i<NB_BONHOMMES;i++){
        if(estEnVie(i, 0))
            return 0;
    }
    return 1;
}

void jouer(){


    jouerBonhommes();
    jouerAnimaux();
    jouerJoueur();

    //verifieToutesCollisions();

    if(dernier())
        gagne();
    if(!joueur.enVie)
        perdu();

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5,5,-5,5,5,600);
    gluLookAt(joueur.pos.x, joueur.pos.y, joueur.pos.z, joueur.pos.x+joueur.direction.x, joueur.pos.y+joueur.direction.y, joueur.pos.z+joueur.direction.z, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //origine();
    dessiner();

    glutSwapBuffers();
    glutPostRedisplay();
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

    joueur.direction.x=2*vitesse*cos(angleY*3.14/180);
    joueur.direction.y=2*vitesse*sin(angleY*3.14/180);
    direction.x = 2*vitesse*cos(angleY*3.14/180+3.14/2);
    direction.y = 2*vitesse*sin(angleY*3.14/180+3.14/2);
    //vueY = x;
    if(y<TAILLE_ECRAN/2-10){
        angleZ++;
        if(angleZ>90) angleZ=90;
    }else if(y>TAILLE_ECRAN/2+10){
        angleZ--;
        if(angleZ<-90) angleZ=-90;
    }

    joueur.direction.z=2*vitesse*sin(angleZ*3.14/180);

    if((clock() - chrono)>100){
        glutWarpPointer(TAILLE_ECRAN/2,TAILLE_ECRAN/2);
        chrono = clock();
    }
}

void GererClavier(unsigned char touche, int x, int y){
    if(debugMode)
        printf("Released : %c en %d %d\n", touche, x, y);

    action = 0;

    //double x2, y2;

    if(touche == 'z'){
        avantInput = 1;
        action = 1;
    }

    if(touche == 'd'){
        droiteInput = 1;
        action = 1;
    }

    if(touche == 's'){
        arriereInput = 1;
        action = 1;
    }

    if(touche == 'q'){
        gaucheInput = 1;
        action = 1;
    }
    if(touche == 'r'){
        envol = (envol+1)%2;
        if(!envol)
            joueur.pos.z = 5;
    }
    if(envol){
        if(touche == 'w' && joueur.pos.z<HAUTEUR_CARTE-10){
            hautInput = 1;
            action = 1;
        }

        if(touche == 'x' && joueur.pos.z>INITIAL_Z){
            basInput = 1;
            action = 1;
        }
    }
    if(touche == '&'){
        exit(0);
    }

}

void GererReleaseClavier(unsigned char touche, int x, int y){
    if(debugMode)
        printf("Released : %c en %d %d\n", touche, x, y);
    if(touche == 'z'){
        avantInput = 0;
    }

    if(touche == 'd'){
        droiteInput = 0;
    }

    if(touche == 's'){
        arriereInput = 0;
    }

    if(touche == 'q'){
        gaucheInput = 0;
    }

    if(envol){
        if(touche == 'w'){
            hautInput = 0;
        }

        if(touche == 'x'){
            basInput = 0;
        }
    }

}

int main(int argc, char **argv) {
    printf("%d, %d, %d, %d\n", gaucheInput, droiteInput, avantInput, arriereInput);
    for(int i = 1; i < argc; ++i){
        if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0){
            debugMode = 1;
            fprintf(stderr, "debug mode\n");
            break;
        }
    }
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
    glFrustum(-5,5,-5,5,20,600);
    gluLookAt(INITIAL_X, INITIAL_Y,INITIAL_Z, INITIAL_X/2, 0, 5, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    //glutSetCursor(GLUT_CURSOR_NONE);
    init();
    direction = (point){0,vitesse,5};

    glutIdleFunc(jouer);
    glutPassiveMotionFunc(GererSouris);
    glutKeyboardFunc(GererClavier);
    glutKeyboardUpFunc(GererReleaseClavier);
    glutMainLoop();

    return 0;
}

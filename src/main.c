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
int vitesseJeu = 1;
int action = 0;
int gaucheInput = 0, droiteInput = 0, avantInput = 0, arriereInput = 0, hautInput = 0, basInput = 0;


double angleY=0;
double angleZ=0;
clock_t chrono;

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

void draw2D() {
    glColor3f(1.0f, 1.0f, 1.0f); // Set the color of the cross to white.
    glBegin(GL_LINES);
    glVertex2f(TAILLE_ECRAN / 2.0f, (TAILLE_ECRAN / 2.0f) - 15); // Start at the middle of the screen on the bottom.
    glVertex2f(TAILLE_ECRAN / 2.0f, (TAILLE_ECRAN / 2.0f) + 15); // Draw to the middle of the screen at the top.
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((TAILLE_ECRAN / 2.0f) - 15, TAILLE_ECRAN / 2.0f); // Start at the middle of the screen on the left.
    glVertex2f((TAILLE_ECRAN / 2.0F) + 15, TAILLE_ECRAN / 2.0f); // Draw to the middle of the screen on the right.
    glEnd();
}


void jouer(){
    
    jouerBonhommes();
    jouerAnimaux();
    jouerJoueur();

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
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    dessiner();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // Save the 3D projection matrix
    glLoadIdentity();
    gluOrtho2D(0, TAILLE_ECRAN, 0, TAILLE_ECRAN); // Set up a 2D orthographic projection matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Disable depth testing and lighting for 2D rendering
    glDisable(GL_DEPTH_TEST);

    // Draw your 2D content here.
    draw2D(); // This is where you'd call your 2D drawing function.

    glEnable(GL_DEPTH_TEST);

    // Restore the original 3D projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
    glutPostRedisplay();
}

void GererSouris(int x, int y){

    if(x==TAILLE_ECRAN/2 && y==TAILLE_ECRAN/2){
        return;
    }
    if(x<TAILLE_ECRAN/2-10){
        angleY+=1.5;
        if(angleY>359) angleY=0;
    }else if(x>TAILLE_ECRAN/2+10){
        angleY-=1.5;
        if(angleY<0) angleY=359;
    }

    joueur.direction.x=2*vitesse*cos(angleY*3.14/180);
    joueur.direction.y=2*vitesse*sin(angleY*3.14/180);
    direction.x = 2*vitesse*cos(angleY*3.14/180+3.14/2);
    direction.y = 2*vitesse*sin(angleY*3.14/180+3.14/2);
    //vueY = x;
    if(y<TAILLE_ECRAN/2-10){
        angleZ+=1.5;
        if(angleZ>90) angleZ=90;
    }else if(y>TAILLE_ECRAN/2+10){
        angleZ-=1.5;
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

void usage(char *s) {
    printf("%s\n", s);
    printf("=========================================\n");
    printf("==============\tUSAGE\t=================\n");
    printf("\t<%s> \t<options>\n\n", s);
    printf("\t\t<options> : \n\t\t<-d OU --debug> \n\tAffiche les messages d'informations\n\n\t\t<-s OU --speed SUIVI DE <i>> \n\tIncrémente ou décrémente la vitesse du jeu. DEFAULT : 2. i COMPRIS ENTRE 1 ET 6\n\n \t\t<-h || --help>\n\tAffiche cette aide\n");
    printf("=========================================\n");

}

int main(int argc, char **argv) {
    int paramSpeed;
    for(int i = 1; i < argc; ++i){
        /*
          -d --debug
          -s --speed default 2
          -h --help
         */
        if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0){
            debugMode = 1;
            fprintf(stderr, "debug mode\n");
            break;
        }
        if((strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--speed") == 0) && i+1 < argc){
            paramSpeed = atoi(argv[i+1]);
            switch(paramSpeed) {
            case 1:
                vitesse = 0.5;
                break;

            case 2:
                vitesse = 1;
                break;
            case 3:
                vitesse = 1.5;
                break;
            case 4:
                vitesse = 2;
                break;
            case 5:
                vitesse = 2.5;
                break;
            case 6:
                vitesse = 3;
                break;

            default:
                usage(argv[0]);
                exit(0);
            }
            break;
        }

        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            usage(argv[0]);
            exit(0);
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
    glutSetCursor(GLUT_CURSOR_NONE);
    init();
    direction = (point){0,vitesse,5};

    glutIdleFunc(jouer);
    glutPassiveMotionFunc(GererSouris);
    glutKeyboardFunc(GererClavier);
    glutKeyboardUpFunc(GererReleaseClavier);
    glutMainLoop();

    return 0;
}

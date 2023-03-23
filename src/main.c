#include "all.h"
#include "interaction.h"
#include "dessin.h"
#include "math.h"

maison maisons[NB_MAISONS];
arbre arbres[NB_ARBRES];
animal animaux[NB_ANIMAUX];
bonhomme bonhommes[NB_BONHOMMES];
rect carte;

point posMaisons[NB_MAISONS];
point posArbres[NB_ARBRES];
point posAnimaux[NB_ANIMAUX];
point posBonhommes[NB_BONHOMMES];

double angle = 0;
position joueur;

int vueY=0;
int vueZ=0;
double angleY=0;
double angleZ=0;

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

void jouer(){
    //glClear(GL_COLOR_BUFFER_BIT);
    //temp
    int xcos = (int)(1000*cos(angle*3.14/180.0));
    int xsin = (int)(1000*sin(angle*3.14/180.0));
    angle+=1;
    if (angle >= 360) angle = 0;
    
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5,5,-5,5,5,2000);
    //gluLookAt(xcos,xsin,xsin, 100,100,100, 1,0,0);
    //glFrustum(joueur.p.x,joueur.p.y,joueur.p.z,5,20,100);
    gluLookAt(joueur.p.x,joueur.p.y,joueur.p.z,joueur.p.x+joueur.directionAvant.x,joueur.p.y+joueur.directionAvant.y,joueur.p.z+joueur.directionAvant.z, 1,0,0);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    origine();
    dessiner();
    //glutPostRedisplay();
    glutSwapBuffers();
}

void GererSouris(int x, int y){
    printf("%d %d\n",x,y);
    x-=TAILLE_ECRAN/2;
    y-=TAILLE_ECRAN/2;
    //joueur.direction.y=joueur.direction.y-y;
	//direction z pas besoin
	if(x<vueY){
		angleY--;
		if(angleY<0) angleY=359;
	}else if(x>vueY){
		angleY++;
		if(angleY>359) angleY=0;
	}
		joueur.directionAvant.x=(int)(10*cos(angleZ*3.14/180));
		joueur.directionAvant.y=(int)(10*sin(angleZ*3.14/180));
	vueY = x;
	if(y<vueZ){
		angleZ--;
		if(angleZ<0) angleZ=359;
	}else if(y>vueZ){
		angleZ++;
		if(angleZ>359) angleZ=0;
	}
		joueur.directionAvant.z=(int)(10*cos(angleZ*3.14/180));
	vueZ = y;
}

void GererClavier(unsigned char touche, int x, int y){
    printf("%c %d %d\n",touche,x,y);
    if(touche == 'z'){
        joueur.p.x+=joueur.directionAvant.x;
        //joueur.p.y+=joueur.directionAvant.y;
    }else if(touche == 'd'){
        //joueur.p.x+=joueur.directionCote.x;
        joueur.p.y+=joueur.directionAvant.y;
    }else if(touche == 's'){
        joueur.p.x-=joueur.directionAvant.x;
        //joueur.p.y-=joueur.directionAvant.y;
    }else if(touche == 'q'){
        //joueur.p.x-=joueur.directionCote.x;
        joueur.p.y-=joueur.directionAvant.y;
    }
}

int main(int argc, char **argv) {	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(TAILLE_ECRAN, TAILLE_ECRAN);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Projet SAI");
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5,5,-5,5,20,1000);
    gluLookAt(500,500,0, 0,0,0, 1,0,0);
    
    glMatrixMode(GL_MODELVIEW);
    
    init();
    joueur.p=(point){500,500,5};
    joueur.directionAvant=(point){10,0,5};
    joueur.directionCote=(point){0,10,5};
    joueur.directionDessus=(point){0,0,0};
    
    glutIdleFunc(jouer);
    glutPassiveMotionFunc(GererSouris);
    glutKeyboardFunc(GererClavier);
    
    glutMainLoop();
    
    return 0;
}
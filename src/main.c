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
	

    jouerBonhommes();
	jouerAnimaux();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5,5,-5,5,5,2000);
    gluLookAt(joueur.pos.x, joueur.pos.y, joueur.pos.z, joueur.pos.x+joueur.direction.x, joueur.pos.y+joueur.direction.y, joueur.pos.z+joueur.direction.z, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    origine();
    dessiner();

    glutSwapBuffers();
}

void GererSouris(int x, int y){
    printf("%d %d\n",x,y);
    x-=TAILLE_ECRAN/2;
    y-=TAILLE_ECRAN/2;
	if(x<vueY){
		angleY--;
		if(angleY<0) angleY=359;
	}else if(x>vueY){
		angleY++;
		if(angleY>359) angleY=0;
	}
	
	joueur.direction.x=(int)(10*cos(angleZ*3.14/180));
	joueur.direction.y=(int)(10*sin(angleZ*3.14/180));
	vueY = x;
	if(y<vueZ){
		angleZ--;
		if(angleZ<-90) angleZ=-90;
	}else if(y>vueZ){
		angleZ++;
		if(angleZ>90) angleZ=90;
	}
	joueur.direction.z=(int)(10*cos(angleZ*3.14/180));
	vueZ = y;
}

void GererClavier(unsigned char touche, int x, int y){
	int x2, y2;
    printf("%c %d %d\n",touche,x,y);
    if(touche == 'z'){
        x2 = joueur.pos.x + joueur.direction.x;
        y2 = joueur.pos.y + joueur.direction.y;
    }else if(touche == 'd'){
        x2 = joueur.pos.x + (int)(10*cos(angleY*3.14/180)-3.14/2);
        y2 = joueur.pos.y + (int)(10*sin(angleY*3.14/180)-3.14/2);
    }else if(touche == 's'){
        x2 = joueur.pos.x-=joueur.direction.x;
        y2 = joueur.pos.y-=joueur.direction.y;
    }else if(touche == 'q'){
        x2 = joueur.pos.x - (int)(10*cos(angleY*3.14/180)+3.14/2);;
        y2 = joueur.pos.y - (int)(10*sin(angleY*3.14/180)+3.14/2);
    } else return;
	
	if(estAutorise(-1, x2, y2)){
		joueur.pos.x = x2;
		joueur.pos.y = y2;
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
    gluLookAt(500, 500,0, 0, 0, 0, 0, 0, 1);
    
    glMatrixMode(GL_MODELVIEW);
    
    init();
    joueur.pos=(point){500,500,5};
    joueur.direction=(point){10,0,5};
	joueur.hitBox = (rect){10,10};
    
    glutIdleFunc(jouer);
    glutPassiveMotionFunc(GererSouris);
    glutKeyboardFunc(GererClavier);
    
    glutMainLoop();
    
    return 0;
}

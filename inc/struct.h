#ifndef STRUCT_H
#define STRUCT_H

#include "GL/gl.h"
#include "GL/glut.h" 


#define NB_PATTES 4

typedef struct s_point {
	int x;
	int y;
	int z;
} point;

typedef struct s_couleur {
	int r;
	int g;
	int b;
} couleur;


typedef struct s_position {
	point p;
	point direction;
} position;

typedef struct s_rect {
	int hauteur;
	int largeur;
	int longueur;
} rect;

typedef struct s_pyramide {
	int hauteur;
	int largeur;
	int longueur;
} pyramide;

typedef struct s_cylindre {
	point centre;
	int rayon;
	int hauteur;
} cylindre;


typedef struct s_boule {
	point centre;
	int rayon;
} boule;


typedef struct s_maison {
	int id;

	position p;
	rect batiment;
	int hauteurToit;

	couleur couleurMur;
	couleur couleurToit;
	
} maison;

typedef struct s_arbre {
	int id;
	position p;

	cylindre tronc;

	boule tete;

	rect hitbox;
} arbre;

typedef struct s_animal {
	int id;

	position p;

	rect corps;

	cylindre pattes[NB_PATTES];

	cylindre cou;
	boule tete;

	rect hitbox;
} animal;


typedef struct s_bonhomme {
	int id;

	position p;

	rect corps;

	cylindre pieds[2];
	cylindre bras[2];

	cylindre cou;

	boule tete;

	rect hitbox;
} bonhomme;


#endif

#ifndef STRUCT_H
#define STRUCT_H


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
	point directionAvant;
	point directionCote;
	point directionDessus;
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
	int rayon;
	int hauteur;
} cylindre;


typedef struct s_boule {
	int rayon;
} boule;


typedef struct s_maison {
	int id;

	point p;
	rect batiment;
	int hauteurToit;

	couleur couleurMur;
	couleur couleurToit;
	
} maison;

typedef struct s_arbre {
	int id;
	point p;

	cylindre tronc;

	boule tete;
} arbre;

typedef struct s_animal {
	int id;

	position p;

	rect corps;

	cylindre pattes;

	cylindre cou;
	boule tete;

	rect hitbox;
} animal;


typedef struct s_bonhomme {
	int id;

	position p;

	rect corps;

	cylindre pieds;
	cylindre bras;

	cylindre cou;

	boule tete;

	rect hitbox;
} bonhomme;

#endif

#ifndef STRUCT_H
#define STRUCT_H

typedef enum {
    JOUEUR,
    BONHOMME,
    ANIMAL,
    ARBRE,
    MAISON
} type;



typedef struct s_point {
    double x;
    double y;
    double z;
} point;

typedef struct s_rect {
    int largeur;
    int longueur;
} rect;

typedef struct s_maison {
    point pos;
    rect hitBox;
} maison;

typedef struct s_arbre {
    point pos;
    rect hitBox;
} arbre;

typedef struct s_animal {
    int enVie;
    int isDepl;
    point pos;
    point previousPos;
    point direction;
    point cible;
    rect hitBox;
} animal;


typedef struct s_bonhomme {
    int enVie;
    int isDepl;
    point pos;
    point previousPos;
    point direction;
    point cible;
    rect hitBox;
} bonhomme;

#endif

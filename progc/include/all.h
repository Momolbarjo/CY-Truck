#ifndef ALL_H
#define ALL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>


#define TAILLE 100
#define MAX_VILLE 10

typedef struct Ville{
	unsigned short nb_fois;	
	unsigned short nb_depart;
	char nom[TAILLE];
}Ville,*pVille;


typedef struct Avl_t{
	Ville elt;
    char hauteur;
    char equilibre;
    struct Avl_t* fg;
    struct Avl_t* fd;
}Avl_t,*pAvl_t;

typedef struct Donnee {
    unsigned int id;
    float min, max, max_min, moy;
} Donnee;


typedef struct Avl {
    struct Donnee donnee;
    char hauteur;
    char equilibre;
    struct Avl* fg;
    struct Avl* fd;
} Avl, *pAvl;


int getch(void);
Donnee extraireDonneeCSV(char *ligne);
void afficherAVLdansSortie(pAvl racine,FILE* sortie, int *n);

pAvl creerArbre(Donnee donnee);
char hauteur(pAvl monAvl); 
void majHauteur(pAvl monAvl);
pAvl rotationDroite(pAvl monAvl);
pAvl rotationGauche(pAvl monAvl);
char equilibre(pAvl monAvl);
pAvl doubleRotationGauche(pAvl myAvl); 
pAvl doubleRotationDroite(pAvl myAvl); 
pAvl equilibrerAVL(pAvl myAvl); 
pAvl insererNoeudAVL(pAvl racine, Donnee donnee);
pAvl construireAVL(FILE *Fichier);
void libererMemoireAVL(pAvl racine);

Ville creerVille(char* nom);
pAvl_t creerArbre_t(Ville maVille);
char hauteur_t(pAvl_t monAvl);
void majHauteur_t(pAvl_t monAvl);
pAvl_t rotationDroite_t(pAvl_t monAvl);
pAvl_t rotationGauche_t(pAvl_t monAvl);
char equilibre_t(pAvl_t monAvl);
pAvl_t doubleRotationGauche_t(pAvl_t monAvl);
pAvl_t doubleRotationDroite_t(pAvl_t monAvl);
pAvl_t equilibrerAVL_t(pAvl_t monAvl);
pAvl_t ajoutAVL_t(pAvl_t monAvl, Ville maVille);
void infixeDecroissant10(pAvl_t monAvl, int* compteur, Ville tab[MAX_VILLE]);
void libererAVL_t(pAvl_t monAvl);
Ville extraireDonneeCSV_2(char *ligne);
pAvl_t traitement(pAvl_t a);
void echanger(pVille a, pVille b);
void tri(pVille tab); 

#endif

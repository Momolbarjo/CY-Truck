#ifndef ALL_H
#define ALL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

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

#endif

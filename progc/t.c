#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TAILLE 50

// DEFINITION DE LA STRUCTURE AVL :


typedef struct Ville{
	unsigned short nb_fois;	
	unsigned short nb_depart;
	char nom[TAILLE];
}Ville,*pVille;


typedef struct Avl{
	pVille elt;
    	char hauteur;
    	struct Avl* fg;
    	struct Avl* fd;
}Avl,*pAvl;


// FONCTIONS POUR LES AVL :


pVille creerVille(char* nom, int num1, int num2){
	pVille nouveau = (pVille)malloc(sizeof(Ville));

	if(nouveau==NULL){
        	printf("Erreur d'allocation mémoire pour 'nouveau' !\n");
       		exit(EXIT_FAILURE);
   	}
   	
   	nouveau->nb_fois = num1;
	nouveau->nb_depart = num2;
   	strcpy(nouveau->nom, nom);
   	
	return nouveau;
}


pAvl creerArbre(pVille maVille){
    	if(maVille == NULL){
    		printf("L'élement de type Ville donné est vide ! \n");
    		exit(EXIT_FAILURE);
    	}
    	
	pAvl monAvl=(pAvl)malloc(sizeof(Avl));
	
    	if(monAvl==NULL){
        	printf("Erreur d'allocation mémoire pour 'monAvl' !\n");
       		exit(EXIT_FAILURE);
   	}

    	monAvl->elt = maVille;
    	monAvl->hauteur=1;
    	monAvl->fg=NULL;
    	monAvl->fd=NULL;

    	return monAvl;
}


char hauteur(pAvl monAvl){
	
	if(monAvl != NULL){
		return monAvl->hauteur;
	}
	
	else{
		return 0;
	}
}


void majHauteur(pAvl monAvl) {
    if (monAvl != NULL) {
        char hauteurG = hauteur(monAvl->fg);
        char hauteurD = hauteur(monAvl->fd);

        if (hauteurG > hauteurD) {
            monAvl->hauteur = hauteurG + 1;
        } else {
            monAvl->hauteur = hauteurD + 1;
        }
    }
}


pAvl rotationDroite(pAvl monAvl) {
    	if (monAvl == NULL || monAvl->fg == NULL) {
        	return monAvl;
    	}

    	pAvl A = monAvl->fg;
    	
    	if (A->fd == NULL) {
        	return monAvl;
    	}

    	pAvl B = A->fd;

    	A->fd = monAvl;
    	monAvl->fg = B;

    	majHauteur(monAvl);
    	majHauteur(A);

    	return A;
}


pAvl rotationGauche(pAvl monAvl) {
    	if (monAvl == NULL || monAvl->fd == NULL) {
        	return monAvl;
    	}

    	pAvl A = monAvl->fd;
    	
    	if (A->fg == NULL) {
        	return monAvl;
    	}

    	pAvl B = A->fg;

    	A->fg = monAvl;
    	monAvl->fd = B;

    	majHauteur(monAvl);
    	majHauteur(A);

    	return A;
}



char equilibre(pAvl monAvl){
	if(monAvl != NULL){
		return hauteur(monAvl->fg) - hauteur(monAvl->fd);
	}
	
	else{
		return 0;
	}
}


pAvl ajoutAVL(pAvl monAvl, pVille maVille) {
    	if(maVille == NULL){
    		printf("L'élement de type Ville donné est vide ! \n");
    		exit(EXIT_FAILURE);
    	}
    	
    	if (monAvl == NULL) {
        	return creerArbre(maVille);
    	}

   	 if (maVille->nb_fois < monAvl->elt->nb_fois) {
       	 	monAvl->fg = ajoutAVL(monAvl->fg, maVille);
    	} 
    	
    	else if (maVille->nb_fois >= monAvl->elt->nb_fois) {
        	monAvl->fd = ajoutAVL(monAvl->fd, maVille);
    	}

    	majHauteur(monAvl);

    	char eq = equilibre(monAvl);

    	if (eq > 1) {
        	if (maVille->nb_fois < monAvl->fg->elt->nb_fois) {
            		return rotationDroite(monAvl);
        	} 
        	
        	else if (maVille->nb_fois >= monAvl->fg->elt->nb_fois) {
            		monAvl->fg = rotationGauche(monAvl->fg);
            		return rotationDroite(monAvl);
        	}
    	}

    	if (eq < -1) {
        	if (maVille->nb_fois < monAvl->fd->elt->nb_fois) {
            		monAvl = rotationGauche(monAvl);
            		return monAvl;
        	} 
        	
        	else if (maVille->nb_fois >= monAvl->fd->elt->nb_fois) {
            		monAvl->fd = rotationDroite(monAvl->fd);
            		return rotationGauche(monAvl);
        	}
    	}

    	return monAvl;
}


void infixeAvl(pAvl monAvl) {
    	if (monAvl != NULL) {
        	if (monAvl->fg != NULL) {
            		infixeAvl(monAvl->fg);
        	}
        	
        	printf("%s %hu \n", monAvl->elt->nom, monAvl->elt->nb_fois);
        	
        	if (monAvl->fd != NULL) {
            		infixeAvl(monAvl->fd);
        	}
    	}
}

void libererAVL(pAvl monAvl){
	
	if(monAvl != NULL){
		libererAVL(monAvl->fg);
		libererAVL(monAvl->fd);
		free(monAvl);
	}
}


void recherche(char* nom, pAvl monAvl, char* test){

	if(monAvl == NULL){
		return;
	}
	
	else if(strcmp(monAvl->elt->nom, nom) == 0){
		*test = 1;
		return;
	}
	
	recherche(nom, monAvl->fg, test);
	recherche(nom, monAvl->fd, test);
					
}


void nb_apparition(pVille maVille, FILE* fichier2, FILE* fichier3){
	unsigned short doublon = 0;
	char chaine2[TAILLE];
	char chaine3[TAILLE];
	
	fseek(fichier2,0,SEEK_SET);
	fseek(fichier3,0,SEEK_SET);
		
	while(fgets(chaine2,TAILLE,fichier2) != NULL && fgets(chaine3,TAILLE,fichier3) != NULL){				
		if(strcmp(maVille->nom,chaine2) == 0){
			if(strcmp(chaine2,chaine3) != 0){
				maVille->nb_fois ++;
				maVille->nb_depart ++;
			}		
		}
			
		memset(chaine2, 0, sizeof(chaine2));
		
		if(strcmp(maVille->nom,chaine3) == 0){
			if(strcmp(chaine2,chaine3) != 0){
				maVille->nb_fois ++;
			}
		}
			
		memset(chaine3, 0, sizeof(chaine3));
	}
	
	fclose(fichier2);
	fclose(fichier3);
}


pAvl ajoutVille(pAvl a){
	FILE* fichier1 = NULL;
	FILE* fichier2 = NULL;
	FILE* fichier3 = NULL;
	
	char chaine1[TAILLE];
	char verif;
	
	pVille maVille = NULL;
	
	fichier1 = fopen("temp/ville.txt","r");
	
	if(fichier1 == NULL){
		printf("ERREUR LORS DE L'OUVERTURE DE ville.txt ! \n");
		exit(1);
	}	
	
	fichier2 = fopen("temp/depart.txt","r");
	
	if(fichier2 == NULL){
		printf("ERREUR LORS DE L'OUVERTURE DE depart.txt ! \n");
		exit(1);
	}
	
	fichier3 = fopen("temp/arrive.txt","r");
	
	if(fichier3 == NULL){
		printf("ERREUR LORS DE L'OUVERTURE DE arrive.txt ! \n");
		exit(1);
	}
	
	while(fgets(chaine1,TAILLE,fichier1) != NULL){
		verif = 0;
		recherche(chaine1,a,&verif);
	
		if(verif != 1){
			maVille = creerVille(chaine1, 0, 0);
			nb_apparition(maVille,fichier2,fichier3);
			a = ajoutAVL(a,maVille);
		}
	}
	

	printf("%s %hu %hu \n",maVille->nom,maVille->nb_fois,maVille->nb_depart );
	
	fclose(fichier1);
	fclose(fichier2);
	fclose(fichier3);

	return a;
}


// MAIN :

int main(void){
	pAvl villeAVL = NULL;
	
	ajoutVille(villeAVL);
	
	infixeAvl(villeAVL);
	
	libererAVL(villeAVL);
	
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TAILLE 50

// DEFINITION DE LA STRUCTURE AVL :

typedef struct Avl{
    	char ville[TAILLE];
    	unsigned short val;
    	char hauteur;
    	struct Avl* fg;
    	struct Avl* fd;
}Avl,*pAvl;


// FONCTIONS POUR LES AVL :

pAvl creerArbre(char* nom, int num){
    
	pAvl monAvl=(pAvl)malloc(sizeof(Avl));

    	if(monAvl==NULL){
        	printf("Erreur d'allocation mÃ©moire !\n");
       		exit(EXIT_FAILURE);
   	}

   	strcpy(monAvl->ville, nom);
    	monAvl->val=num;
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


pAvl ajoutAVL(pAvl monAvl, char* nom, int num) {
    if (monAvl == NULL) {
        return creerArbre(nom, num);
    }

    if (num < monAvl->val) {
        monAvl->fg = ajoutAVL(monAvl->fg, nom, num);
    } else if (num >= monAvl->val) {
        monAvl->fd = ajoutAVL(monAvl->fd, nom, num);
    }

    majHauteur(monAvl);

    char eq = equilibre(monAvl);

    if (eq > 1) {
        if (num < monAvl->fg->val) {
            return rotationDroite(monAvl);
        } else if (num >= monAvl->fg->val) {
            monAvl->fg = rotationGauche(monAvl->fg);
            return rotationDroite(monAvl);
        }
    }

    if (eq < -1) {
        if (num < monAvl->fd->val) {
            monAvl = rotationGauche(monAvl);
            return monAvl;
        } else if (num >= monAvl->fd->val) {
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
        printf("%s %hu \n", monAvl->ville, monAvl->val);
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
	
	else if(strcmp(monAvl->ville, nom) == 0){
		*test = 1;
		return;
	}
	
	recherche(nom, monAvl->fg, test);
	recherche(nom, monAvl->fd, test);
					
}



// MAIN :

int main(void){
	
	FILE* fichier1 = NULL;
	FILE* fichier2 = NULL;
	FILE* fichier3 = NULL;
	unsigned short total, compteur1, compteur2, doublon; 
	char verif;
	char chaine1[TAILLE];
	char chaine2[TAILLE];
	char chaine3[TAILLE];
	
	pAvl villeAVL = NULL;
	
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
	
		fseek(fichier2,0,SEEK_SET);
		fseek(fichier3,0,SEEK_SET);
		
		total = 0;
		doublon = 0;
		compteur1 = 0;
		compteur2 = 0;
		verif = 0;
		
		while(fgets(chaine2,TAILLE,fichier2) != NULL && fgets(chaine3,TAILLE,fichier3) != NULL){			
			
			if(strcmp(chaine2,chaine3) == 0 && strcmp(chaine1,chaine2)== 0){
				doublon++;
			}
		
			if(strcmp(chaine1,chaine2) == 0){
				compteur1++;
			}
			
			memset(chaine2, 0, sizeof(chaine2));
		
			if(strcmp(chaine1,chaine3) == 0){
				compteur2++;
			}
			
			memset(chaine3, 0, sizeof(chaine3));
		}
	
		total = compteur1 + compteur2 - doublon;
	
	
		recherche(chaine1,villeAVL,&verif);
		
		if(verif != 1){
			villeAVL = ajoutAVL(villeAVL,chaine1,total);
		}
		
		printf("%s %hu \n",chaine1,total);
	}
	
	fclose(fichier1);
	fclose(fichier2);
	fclose(fichier3);
	
	infixeAvl(villeAVL);
	
	libererAVL(villeAVL);
		
	
	return 0;
}

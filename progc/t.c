#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TAILLE 50


// DEFINITION DE LA STRUCTURE AVL :

typedef struct Avl{
    	char ville[TAILLE];
    	int val;
    	int hauteur;
    	struct Avl* fg;
    	struct Avl* fd;
}Avl,*pAvl;


// FONCTIONS POUR LES AVL :

pAvl creerArbre(char* nom, int num){
    
	pAvl monAvl=(pAvl)malloc(sizeof(Avl));

    	if(monAvl==NULL){
        	printf("Erreur d'allocation mémoire !\n");
       		exit(EXIT_FAILURE);
   	}

   	strcpy(monAvl->ville, nom);
    	monAvl->val=num;
    	monAvl->hauteur=1;
    	monAvl->fg=NULL;
    	monAvl->fd=NULL;

    	return monAvl;
}


int hauteur(pAvl monAvl){
	
	if(monAvl != NULL){
		return monAvl->hauteur;
	}
	
	else{
		return 0;
	}
}


void majHauteur(pAvl monAvl){
	
	if(monAvl != NULL){
		int hauteurG = hauteur(monAvl->fg);
		int hauteurD = hauteur(monAvl->fd);
		
		if(hauteurG > hauteurD){
			monAvl->hauteur = hauteurG + 1;
		}

		else{
			monAvl->hauteur = hauteurD + 1;
		}
	}
}

pAvl rotationDroite(pAvl monAvl){

	pAvl A = monAvl->fg;
    	pAvl B = A->fd;
    
    	A->fd = monAvl;
    	monAvl->fg = B;
    
	majHauteur(monAvl);
	majHauteur(A);

   	return A;
}

pAvl rotationGauche(pAvl monAvl){

	pAvl A = monAvl->fd;
    	pAvl B = A->fg;
    
    	A->fg = monAvl;
    	monAvl->fd = B;
    
	majHauteur(monAvl);
	majHauteur(A);

   	return A;
}


int equilibre(pAvl monAvl){
	
	if(monAvl != NULL){
		return hauteur(monAvl->fg) - hauteur(monAvl->fd);
	}
	
	else{
		return 0;
	}
}


pAvl ajoutAVL(pAvl monAvl, char* nom, int num){
	
	if(monAvl == NULL){
		return creerArbre(nom, num);
	}

	else if(num < monAvl->val){
		monAvl->fg = ajoutAVL(monAvl->fg, nom, num);
	}
	
	else if(num >= monAvl->val){
		monAvl->fd = ajoutAVL(monAvl->fd, nom, num);
	}
	
	
	majHauteur(monAvl);
	
	int eq = equilibre(monAvl);
	
	if(eq > 1){
		
		if(num < monAvl->fg->val){
			return rotationDroite(monAvl);
		}
		
		else if(num >= monAvl->fg->val){
			monAvl->fg = rotationGauche(monAvl->fg);
			return rotationDroite(monAvl);
		}
	}
	
	if(eq < -1){
		
		if(num < monAvl->fd->val){
			return rotationGauche(monAvl);
		}
		
		else if(num >= monAvl->fd->val){
			monAvl->fd = rotationDroite(monAvl->fd);
			return rotationGauche(monAvl);
		}
	}
	
	return monAvl;
}	


void infixeAvl(pAvl monAvl){
	
	if(monAvl != NULL){
		infixeAvl(monAvl->fg);
		printf("%s %d \n",monAvl->ville,monAvl->val);
		infixeAvl(monAvl->fd);
	}
}

void libererAVL(pAvl monAvl){
	
	if(monAvl != NULL){
		libererAVL(monAvl->fg);
		libererAVL(monAvl->fd);
		free(monAvl);
	}
}


void recherche(char* nom, pAvl monAvl, int* test){

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
	int total, compteur1, compteur2, doublon, verif;
	char chaine1[TAILLE];
	char chaine2[TAILLE];
	char chaine3[TAILLE];
	
	pAvl villeAVL = NULL;
	
	fichier1 = fopen("ville.txt","r");
	
	if(fichier1 == NULL){
		printf("ERREUR LORS DE L'OUVERTURE DE ville.txt ! \n");
		exit(1);
	}	
	
	fichier2 = fopen("depart.txt","r");
	
	if(fichier2 == NULL){
		printf("ERREUR LORS DE L'OUVERTURE DE depart.txt ! \n");
	}
	
	fichier3 = fopen("arrive.txt","r");
	
	if(fichier3 == NULL){
		printf("ERREUR LORS DE L'OUVERTURE DE arrive.txt ! \n");
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
		
		printf("%s %d \n",chaine1,total);
	}
	
	fclose(fichier1);
	fclose(fichier2);
	fclose(fichier3);
	
	infixeAvl(villeAVL);
	
	libererAVL(villeAVL);
		
	
	return 0;
}

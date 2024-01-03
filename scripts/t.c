#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TAILLE 50


// DEFINITION DE LA STRUCTURE AVL :

typedef struct Avl{
    char ville[TAILLE];
    int val;
    int equilibre;
    struct Avl* fg;
    struct Avl* fd;
}Avl,*pAvl;


// FONCTIONS min ET max :

int min2(int a, int b){
	
	if(a >= b){
		return b;
	}
	
	else{
		return a;
	}
}


int min3(int a, int b, int c){

	if(a <= b && a <= c){
		return a;
	}
	
	else if(b <= a && b <= c){
		return b;
	}

	else if(c <= a && c <= b){
		return c;
	}
}


int max2(int a, int b){
	
	if(a <= b){
		return b;
	}
	
	else{
		return a;
	}
}


int max3(int a, int b, int c){

	if(a >= b && a >= c){
		return a;
	}
	
	else if(b >= a && b >= c){
		return b;
	}

	else if(c >= a && c >= b){
		return c;
	}
}


// FONCTIONS POUR LES AVL :

pAvl creerArbre(char* nom, int num){
    pAvl monAvl=(pAvl)malloc(sizeof(Avl));

    if(monAvl==NULL){
        fprintf(stderr,"Erreur d'allocation mémoire !\n");
        exit(EXIT_FAILURE);
    }

    strcpy(monAvl->ville, nom);
    monAvl->val=num;
    monAvl->equilibre=0;
    monAvl->fg=NULL;
    monAvl->fd=NULL;

    return monAvl;
}


pAvl rotationGauche(pAvl monAvl){

    pAvl pivot;
    int eqA,eqB;

    pivot=monAvl->fd;
    monAvl->fd=pivot->fg;
    pivot->fg=monAvl;

    eqA=monAvl->equilibre;
    eqB=pivot->equilibre;

    monAvl->equilibre=eqA-max2(eqB,0)-1;
    pivot->equilibre= min3(eqA-2,eqA+eqB-2,eqB-1);

    monAvl=pivot;

    return monAvl;
}

pAvl rotationDroite(pAvl monAvl){

    pAvl pivot;
    int eqA,eqB;

    pivot=monAvl->fg;
    monAvl->fg=pivot->fd;
    pivot->fd=monAvl;

    eqA=monAvl->equilibre;
    eqB=pivot->equilibre;

    monAvl->equilibre=eqA-min2(eqB,0)+1;
    pivot->equilibre= max3(eqA+2,eqA+eqB+2,eqB+1);

    monAvl=pivot;

    return monAvl;
}


pAvl doubleRotationGauche(pAvl monAvl){
    pAvl pivot;
    monAvl->fd=rotationDroite(monAvl->fd);
    
    return rotationGauche(monAvl);
}

pAvl doubleRotationDroite(pAvl monAvl){
    pAvl pivot;
    monAvl->fg=rotationGauche(monAvl->fg);
    
    return rotationDroite(monAvl);
}


pAvl equilibrerAVL(pAvl monAvl){
    if(monAvl->equilibre >=2 ){
        if(monAvl->fd->equilibre >= 0){
            return rotationGauche(monAvl);
        }
        else{
            return doubleRotationGauche(monAvl);
        }
    }
    else if(monAvl->equilibre <= -2){
        if(monAvl->fg->equilibre <=0){
            return rotationDroite(monAvl);
        }
        else{
            return doubleRotationDroite(monAvl);
        }
    }
    return monAvl;
}


pAvl ajoutAVL(pAvl monAvl, char* nom, int num){
    
    printf("caca \n");
    if(monAvl == NULL){
        monAvl = creerArbre(nom, num);
        return monAvl;
    }

    pAvl temp = monAvl;
    pAvl parent = NULL;

    while(temp != NULL){
        parent = temp;

        if(temp->val < num){
            temp = temp->fd;
        }
        else{
            temp = temp->fg;
        }
    }

    if(parent->val < num){
        parent->fd = creerArbre(nom, num);
    }
    else{
        parent->fg = creerArbre(nom, num);
    }

    //monAvl = equilibrerAVL(monAvl); 
 
    return monAvl;
}

/*
pAvl ajoutAVL(pAvl monAvl, char* nom, int num){
	
	if(monAvl == NULL){
		monAvl = creerArbre(nom, num);
		return monAvl;
	}

	pAvl temp = monAvl;
	
	while(temp != NULL){
		
		if(temp->val < num){
			temp = temp->fd;
		}
		
		else{
			temp = temp->fg;
		}
	}
	
	temp = creerArbre(nom,num);
	//monAvl = equilibrerAVL(monAvl);
	
	return monAvl;
}	
*/

void infixeAvl(pAvl monAvl){
	
	if(monAvl == NULL){
		return;
	}
	
	infixeAvl(monAvl->fg);
	printf("%s %d \n",monAvl->ville,monAvl->val);
	infixeAvl(monAvl->fd);
}


// AUTRES FONCTIONS :

void dejaFait(char* nom, pAvl monAvl, int* test){

	if(monAvl == NULL){
		return;
	}
	
	if(strcmp(monAvl->ville, nom) == 0){
		*test = 1;
		return;
	}
	
	dejaFait(nom, monAvl->fg, test);
	dejaFait(nom, monAvl->fd, test);
					
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
	
	while(fgets(chaine1,TAILLE,fichier1) != NULL){
	
	total = 0;
	doublon = 0;
	compteur1 = 0;
	compteur2 = 0;
	verif = 0;
	
	fichier2 = fopen("depart.txt","r");
	
	if(fichier2 == NULL){
		printf("ERREUR LORS DE L'OUVERTURE DE depart.txt ! \n");
	}
	
	fichier3 = fopen("arrive.txt","r");
	
	if(fichier3 == NULL){
		printf("ERREUR LORS DE L'OUVERTURE DE arrive.txt ! \n");
	}
		
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
	
	fclose(fichier2);
	fclose(fichier3);
	
	total = compteur1 + compteur2 - doublon;
	
	
	dejaFait(chaine1,villeAVL,&verif);
	
	
	if(verif != 1){
		villeAVL = ajoutAVL(villeAVL,chaine1,total);
	}
	
	
	}
	
	fclose(fichier1);
	
	infixeAvl(villeAVL);
	
		
	
	return 0;
}

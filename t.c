#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TAILLE 100
#define MAX_VILLE 10

// DEFINITION DE LA STRUCTURE AVL ET DE LA STRUCTURE VILLE :


typedef struct Ville{
	unsigned short nb_fois;	
	unsigned short nb_depart;
	char nom[TAILLE];
}Ville,*pVille;


typedef struct Avl{
	Ville elt;
    	char hauteur;
    	char equilibre;
    	struct Avl* fg;
    	struct Avl* fd;
}Avl,*pAvl;


// FONCTIONS POUR LES AVL :


Ville creerVille(char* nom){
	Ville nouveau;
   	int i;
   	
   	nouveau.nb_fois = 0;
	nouveau.nb_depart = 0;
   	strcpy(nouveau.nom, nom);
   	
	return nouveau;
}


pAvl creerArbre(Ville maVille){
	pAvl monAvl=(pAvl)malloc(sizeof(Avl));
	
    	if(monAvl==NULL){
        	fprintf(stderr,"Erreur d'allocation mémoire pour 'monAvl' !\n");
       		exit(EXIT_FAILURE);
   	}

    	monAvl->elt = maVille;
    	monAvl->hauteur=1;
    	monAvl->fg=NULL;
    	monAvl->fd=NULL;
	monAvl->equilibre=0;
	
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


pAvl doubleRotationGauche(pAvl monAvl){
    	monAvl->fd = rotationDroite(monAvl->fd);
    	return rotationGauche(monAvl);
}


pAvl doubleRotationDroite(pAvl monAvl){
	monAvl->fg = rotationGauche(monAvl->fg);
    	return rotationDroite(monAvl);
}


pAvl equilibrerAVL(pAvl monAvl) {
    	if (monAvl == NULL){
        	return NULL;
    	}

    	if (monAvl->equilibre >= 2){
        	if (monAvl->fd != NULL && monAvl->fd->equilibre >= 0){
            		return rotationGauche(monAvl);
        	} 
        
        
        	else{
            		return doubleRotationGauche(monAvl);
    		} 
    	}
    	
    	else if (monAvl->equilibre <= -2) {
        	
        	if (monAvl->fg != NULL && monAvl->fg->equilibre <= 0) {
            		return rotationDroite(monAvl);
        	} 
        
        	else {
            		return doubleRotationDroite(monAvl);
        	}
    	}
    
    	return monAvl;
}


pAvl ajoutAVL(pAvl monAvl, Ville maVille) {
    	if (monAvl == NULL) {
        	return creerArbre(maVille);
    	}

    	if (maVille.nb_fois < monAvl->elt.nb_fois) {
       	 	monAvl->fg = ajoutAVL(monAvl->fg, maVille);
    	} 
    	
    	else if (maVille.nb_fois >= monAvl->elt.nb_fois) {
        	monAvl->fd = ajoutAVL(monAvl->fd, maVille);
    	}
	
    	monAvl->equilibre = equilibre(monAvl);

    	return equilibrerAVL(monAvl);
}


void infixeDecroissant10(pAvl monAvl, int* compteur, Ville tab[MAX_VILLE]) {
    	if (monAvl != NULL && *compteur < MAX_VILLE) {
        	
        	if (monAvl->fd != NULL) {
            		infixeDecroissant10(monAvl->fd, compteur, tab);
        	}
        
        	if(*compteur < MAX_VILLE){
        		tab[*compteur] = monAvl->elt;
        		(*compteur) ++;
        	}
        	
        	if (monAvl->fg != NULL && *compteur < MAX_VILLE) {
            		infixeDecroissant10(monAvl->fg, compteur, tab);
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


// FONCTIONS DU TRAITEMENT -t :


Ville extraireDonneeCSV_2(char *ligne) {
    	Ville ville;
    	
    	char nombre_elem = sscanf(ligne, "%[^,],%hu,%hu", ville.nom, &(ville.nb_fois), &(ville.nb_depart));
    	
    	if(nombre_elem != 3){
        	fprintf(stderr, "Erreur, le/les types de données de votre fichier CSV ne sont pas adaptés\n");
        	exit(EXIT_FAILURE);
    	}
    	
    	return ville;
}


pAvl traitement(pAvl a){
	FILE* fichier = NULL;
	char chaine[TAILLE];
	Ville ville;
	fichier = fopen("temp/t1.csv","r");
	
	if(fichier == NULL){
		fprintf(stderr,"Erreur lors de l'ouverture du fichier t1.csv ! \n");
		exit(EXIT_FAILURE);
	}
	   
	while(fgets(chaine, TAILLE, fichier) != NULL){
        	ville = extraireDonneeCSV_2(chaine);
        	a = ajoutAVL(a, ville);
    	}
    	
    	fclose(fichier);
	
	return a;	
}


void echanger(pVille a, pVille b) {
    	pVille temp = (pVille)malloc(sizeof(Ville));
    	
    	strcpy(temp->nom,a->nom);
    	temp->nb_fois = a->nb_fois;
    	temp->nb_depart = a->nb_depart;
    	
    	strcpy(a->nom,b->nom);
    	a->nb_fois = b->nb_fois;
    	a->nb_depart = b->nb_depart;
    	
    	strcpy(b->nom,temp->nom);
    	b->nb_fois = temp->nb_fois;
    	b->nb_depart = temp->nb_depart;
    	
    	free(temp);
}


void tri(pVille tab) {
    	pVille temp;
    	for(char i=0; i<MAX_VILLE; i++){
        	for(char j=0; j<MAX_VILLE-i-1; j++){
            		if(strcmp(tab[j].nom,tab[j+1].nom) > 0){
                		echanger(&tab[j],&tab[j+1]);
            		}
        	}
    	}
}
	



// MAIN :

int main(void){
	pAvl villeAVL = NULL;
	int c = 0;
	Ville tableau[MAX_VILLE];
	
	villeAVL = traitement(villeAVL);
	
	
	if(villeAVL == NULL){
		fprintf(stderr,"L'avl est vide !!!\n");
		exit(EXIT_FAILURE);
	}
	
	infixeDecroissant10(villeAVL,&c,tableau);
	
	tri(tableau);
	
	for(int i=0;i<MAX_VILLE;i++){
		printf("%s;%hu;%hu\n",tableau[i].nom,tableau[i].nb_fois,tableau[i].nb_depart);
	}
	
	
	
	libererAVL(villeAVL);
	
	
	return 0;
}

/*
TRAITEMENT [T] : les 10 villes les plus traversées : option -t
Pour ce traitement, vous compterez le nombre de trajets qui parcourent
chaque ville, ainsi que le nombre de fois où ces villes ont été des villes de
départ de trajets.
Une ville n’est traversée qu’une seule fois par trajet, mais forcément elle
peut apparaître deux fois dans les données, une fois comme ville de
départ d’une étape, et une autre fois comme ville d’arrivée de l’étape
précédente. Il vous faudra gérer ce cas un peu particulier.
A la fin du traitement, vous ne conserverez que les 10 premières villes
avec le plus de trajets, par ordre alphabétique.
Votre programme devra créer un graphique de type histogramme
regroupé. On retrouvera en abscisse les noms des villes, par ordre
alphabétique, et en ordonnée le nombre de trajets.
Pour chaque ville, il y aura 2 barres verticales, celle de gauche indiquera
le nombre de trajets total qui traversent cette ville, et celle de droite le
nombre de fois où cette ville est la ville de départ d’un trajet.
 Attention :
Si vous tentez de réaliser ce traitement uniquement à l’aide d’un script
Shell et de commandes Unix, vous ne recevrez aucun point pour le
traitement lui-même (mais vous pourrez avoir les points sur la partie
graphique si l’image est générée correctement malgré tout). Il est donc
obligatoire de passer par un programme C pour effectuer le tri des
données : l’utilisation d’une structure de type AVL est obligatoire. Aucune
commande Unix de type ‘sort’ ne doit être appelée ici.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define TAILLE 50
#define ROUTE 7
#define MAXI 1000

// DEFINITION DE LA STRUCTURE AVL :


typedef struct Ville{
	unsigned short nb_fois;	
	unsigned short nb_depart;
	char nom[TAILLE];
	unsigned short id[MAXI];
}Ville,*pVille;


typedef struct Avl{
	pVille elt;
    	char hauteur;
    	char equilibre;
    	struct Avl* fg;
    	struct Avl* fd;
}Avl,*pAvl;


// FONCTIONS POUR LES AVL :


pVille creerVille(char* nom){
	pVille nouveau = (pVille)malloc(sizeof(Ville));

	if(nouveau==NULL){
        	printf("Erreur d'allocation mémoire pour 'nouveau' !\n");
       		exit(EXIT_FAILURE);
   	}
   	
   	int i;
   	
   	nouveau->nb_fois = 0;
	nouveau->nb_depart = 0;
   	strcpy(nouveau->nom, nom);
   	
   	for(i=0;i<MAXI;i++){
   		nouveau->id[i] = -1;
   	}
   	
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


pAvl ajoutAVL(pAvl monAvl, pVille maVille) {
    	if (monAvl == NULL) {
        	return creerArbre(maVille);
    	}

    	if (maVille->nb_fois < monAvl->elt->nb_fois) {
       	 	monAvl->fg = ajoutAVL(monAvl->fg, maVille);
    	} 
    	
    	else if (maVille->nb_fois >= monAvl->elt->nb_fois) {
        	monAvl->fd = ajoutAVL(monAvl->fd, maVille);
    	}

    	monAvl->equilibre = equilibre(monAvl);

    	return equilibrerAVL(monAvl);
}



/*
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
*/

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



int recherche(pAvl *monAvl, char *nom, char type, unsigned short route) {
    if (*monAvl == NULL) {
        // Si la ville n'est pas trouvée, créez-la et ajoutez-la à l'AVL
        pVille nouvelleVille = creerVille(nom);
        if (type == 1) {
            nouvelleVille->nb_depart = 1;
        }
        nouvelleVille->nb_fois = 1;
        *monAvl = ajoutAVL(*monAvl, nouvelleVille);
        return 1; // Nouvelle ville ajoutée
    } else {
        if (strcmp((*monAvl)->elt->nom, nom) == 0) {
            // Si la ville existe déjà, mettez à jour ses données
            if (type == 1) {
                (*monAvl)->elt->nb_depart++;
            }
            (*monAvl)->elt->nb_fois++;
            return 0; // Ville existante mise à jour
        }
        if (strcmp(nom, (*monAvl)->elt->nom) < 0) {
            return recherche(&(*monAvl)->fg, nom, type, route);
        } else {
            return recherche(&(*monAvl)->fd, nom, type, route);
        }
    }
}



pAvl ajoutVille(pAvl a, char* nom){
	
	pVille maVille = creerVille(nom);
	a = ajoutAVL(a,maVille);
	return a;
}


pAvl traitement(pAvl a){
	FILE* fichier1 = NULL;
	FILE* fichier2 = NULL;
	FILE* fichier3 = NULL;
	FILE* fichier4 = NULL;
	
	fichier1 = fopen("temp/id.csv","r");
	fichier2 = fopen("temp/step.csv","r");
	fichier3 = fopen("temp/depart.csv","r");
	fichier4 = fopen("temp/arrive.csv","r");
	
	if(fichier1 == NULL || fichier2 == NULL || fichier3 == NULL || fichier4 == NULL){
		printf("c'est la merde là");
		exit(EXIT_FAILURE);
	}
	
	char nom1[TAILLE], nom2[TAILLE], verif, step_[2], step, routeid_[ROUTE];
	unsigned short routeid;
	
	while(fgets(routeid_,ROUTE,fichier1) != NULL && fgets(step_,2,fichier2) != NULL && fgets(nom1,TAILLE,fichier3) != NULL && fgets(nom2,TAILLE,fichier4) != NULL){
		
		step = atoi(step_);
		routeid = atoi(routeid_);
		
		verif = 0;
		
		if(step == 1){
			verif = recherche(nom1,a,1,routeid);
			
			if(verif != 1){
				a = ajoutVille(a,nom1);
			}
		}
		
		else{
			verif = recherche(nom1,a,0,routeid);
			
			if(verif != 1){
				a = ajoutVille(a,nom1);
			}	
		}
		
		verif = recherche(nom2,a,0,routeid);
			
		if(verif != 1){
			ajoutVille(a,nom2);
		}	
	}
	
	fclose(fichier1);
	fclose(fichier2);
	fclose(fichier3);
	fclose(fichier4);
	
	return a;
}


// Utilitaire pour comparer deux villes
int comparerVilles(const void *a, const void *b) {
    const Ville *villeA = (const Ville *)a;
    const Ville *villeB = (const Ville *)b;

    // Comparaison basée d'abord sur le nombre de fois traversées, puis alphabétiquement
    if (villeA->nb_fois == villeB->nb_fois) {
        return strcmp(villeA->nom, villeB->nom);
    }
    return villeB->nb_fois - villeA->nb_fois; // Pour trier en ordre décroissant
}

// Fonction récursive pour ajouter les villes à un tableau
void ajouterVillesAuTableau(pAvl monAvl, Ville *villes, int *index) {
    if (monAvl != NULL) {
        ajouterVillesAuTableau(monAvl->fg, villes, index);
        villes[*index] = *(monAvl->elt);
        (*index)++;
        ajouterVillesAuTableau(monAvl->fd, villes, index);
    }
}

// Fonction pour extraire les 10 villes les plus traversées
void extraireTopVilles(pAvl monAvl, Ville topVilles[10]) {
    Ville *toutesLesVilles = malloc(MAX_VILLES * sizeof(Ville));
    int index = 0;

    ajouterVillesAuTableau(monAvl, toutesLesVilles, &index);

    // Trier les villes par nombre de fois traversées et nom
    qsort(toutesLesVilles, index, sizeof(Ville), comparerVilles);

    // Copier les 10 premières villes
    for (int i = 0; i < 10 && i < index; i++) {
        topVilles[i] = toutesLesVilles[i];
    }

    free(toutesLesVilles);
}


// MAIN :

int main(void){
	pAvl villeAVL = NULL;
	
	villeAVL = traitement(villeAVL);
	
	if(villeAVL == NULL){
		printf("caca\n");
	}
	
	infixeAvl(villeAVL);
	
	libererAVL(villeAVL);
	
	return 0;
}

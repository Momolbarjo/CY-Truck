#include "all.h"

//Fichier comportant toutes les fonctions essentielles à l'utilisation des AVL

//Fonction qui créer un neud d'AVL (pour le -s)
pAvl creerArbre(Donnee donnee) {
    pAvl fils = malloc(sizeof(Avl));
    if (fils == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }
    fils->donnee = donnee;
    fils->hauteur = 1;
    fils->equilibre = 0;
    fils->fd = NULL;
    fils->fg = NULL;
    return fils;
}

//Fonction qui calcule la hauteur d'un noeud de l'AVL (pour le -s)
char hauteur(pAvl monAvl) {
    if (monAvl != NULL) {
        return monAvl->hauteur;
    } 
    else {
        return 0;
    }
}

//Fonction qui met à jour la hauteur d'un noeud de l'AVL (pour le -s)
void majHauteur(pAvl monAvl) {
    if (monAvl != NULL) {
        char hauteurG = hauteur(monAvl->fg);
        char hauteurD = hauteur(monAvl->fd);

        if (hauteurG > hauteurD) {
            monAvl->hauteur = hauteurG + 1;
        } 
        else {
            monAvl->hauteur = hauteurD + 1;
        }
    }
}

//Fonction qui effectue une rotation droite d'un noeud de l'AVL (pour l'équilibrage) (pour le -s)
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

//Fonction qui effectue une rotation gauche d'un noeud de l'AVL (pour l'équilibrage) (pour le -s)
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

//Fonction qui calcule l'équilibre d'un noeud d'AVL (pour le -s)
char equilibre(pAvl monAvl) {
    if (monAvl != NULL) {
        return hauteur(monAvl->fg) - hauteur(monAvl->fd);
    } 
    else {
        return 0;
    }
}

//Fonction qui effectue une double rotation gauche d'un noeud de l'AVL (pour l'équilibrage) (pour le -s)
pAvl doubleRotationGauche(pAvl monAvl) {
    monAvl->fd = rotationDroite(monAvl->fd);
    return rotationGauche(monAvl);
}

//Fonction qui effectue une double rotation droite d'un noeud de l'AVL (pour l'équilibrage) (pour le -s)
pAvl doubleRotationDroite(pAvl monAvl) {
    monAvl->fg = rotationGauche(monAvl->fg);
    return rotationDroite(monAvl);
}

//Fonction qui équilibre un noeud de l'AVL (utilisation des rotations) (pour le -s)
pAvl equilibrerAVL(pAvl monAvl) {
    if (monAvl == NULL) {
        return NULL;
    }

    if (monAvl->equilibre >= 2) {
        if (monAvl->fd != NULL && monAvl->fd->equilibre >= 0) {
            return rotationGauche(monAvl);
        } 
        else {
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

//Fonction qui insère un nouveau noeud dans un AVL (pour le -s)
pAvl insererNoeudAVL(pAvl racine, Donnee donnee) {
    if (racine == NULL) {
        return creerArbre(donnee);
    }

    if (donnee.max_min < racine->donnee.max_min) {
        racine->fg = insererNoeudAVL(racine->fg, donnee);
    } 
    else if (donnee.max_min > racine->donnee.max_min) {
        racine->fd = insererNoeudAVL(racine->fd, donnee);
    } 
    else {
        return racine;
    }

    racine->equilibre = hauteur(racine->fg) - hauteur(racine->fd);

    return equilibrerAVL(racine);
}

//Fonction qui cronstruit l'AVL comportant les données du traitement effectué (pour le -s)
pAvl construireAVL(FILE *Fichier) {
    if (Fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    pAvl racine = NULL;
    char ligne[256]; // On suppose qu'une ligne a au plus 256 caractères

    while (fgets(ligne, sizeof(ligne), Fichier) != NULL) {
        Donnee donnee = extraireDonneeCSV(ligne);
        racine = insererNoeudAVL(racine, donnee);
    }

    fclose(Fichier);
    return racine;
}

//Fonction qui libère la mémoire alloué d'un noeud d'AVL (pour le -s)
void libererMemoireAVL(pAvl racine) {
    if (racine != NULL) {
        libererMemoireAVL(racine->fg);
        libererMemoireAVL(racine->fd);
        free(racine);
    }
}

//Fonction qui créer un élément de la structure Ville (pour le -t)
Ville creerVille(char* nom){
	Ville nouveau;
   	int i;
   	
   	nouveau.nb_fois = 0;
	nouveau.nb_depart = 0;
   	strcpy(nouveau.nom, nom);
   	
	return nouveau;
}

//Fonction qui créer un neud d'AVL (pour le -t)
pAvl_t creerArbre_t(Ville maVille){
	pAvl_t monAvl=(pAvl_t)malloc(sizeof(Avl_t));
	
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

//Fonction qui calcule la hauteur d'un noeud de l'AVL (pour le -t)
char hauteur_t(pAvl_t monAvl){
	
	if(monAvl != NULL){
		return monAvl->hauteur;
	}
	
	else{
		return 0;
	}
}


//Fonction qui met à jour la hauteur d'un noeud de l'AVL (pour le -t)
void majHauteur_t(pAvl_t monAvl) {
    if (monAvl != NULL) {
        char hauteurG = hauteur_t(monAvl->fg);
        char hauteurD = hauteur_t(monAvl->fd);

        if (hauteurG > hauteurD) {
            monAvl->hauteur = hauteurG + 1;
        } else {
            monAvl->hauteur = hauteurD + 1;
        }
    }
}

//Fonction qui effectue une rotation droite d'un noeud de l'AVL (pour l'équilibrage) (pour le -t)
pAvl_t rotationDroite_t(pAvl_t monAvl) {
    	if (monAvl == NULL || monAvl->fg == NULL) {
        	return monAvl;
    	}

    	pAvl_t A = monAvl->fg;
    	
    	if (A->fd == NULL) {
        	return monAvl;
    	}

    	pAvl_t B = A->fd;

    	A->fd = monAvl;
    	monAvl->fg = B;

    	majHauteur_t(monAvl);
    	majHauteur_t(A);

    	return A;
}

//Fonction qui effectue une rotation gauche d'un noeud de l'AVL (pour l'équilibrage) (pour le -t)
pAvl_t rotationGauche_t(pAvl_t monAvl) {
    	if (monAvl == NULL || monAvl->fd == NULL) {
        	return monAvl;
    	}

    	pAvl_t A = monAvl->fd;
    	
    	if (A->fg == NULL) {
        	return monAvl;
    	}

    	pAvl_t B = A->fg;

    	A->fg = monAvl;
    	monAvl->fd = B;

    	majHauteur_t(monAvl);
    	majHauteur_t(A);

    	return A;
}


// Fonction qui calcule l'équilibre d'un noeud de l'AVL (pour le -t)
char equilibre_t(pAvl_t monAvl){ 
	if(monAvl != NULL){
		return hauteur_t(monAvl->fg) - hauteur_t(monAvl->fd);
	}
	
	else{
		return 0;
	}
}
 
//Fonction qui effectue une double rotation gauche d'un noeud de l'AVL (pour l'équilibrage) (pour le -t)
pAvl_t doubleRotationGauche_t(pAvl_t monAvl){
    	monAvl->fd = rotationDroite_t(monAvl->fd);
    	return rotationGauche_t(monAvl);
}

//Fonction qui effectue une double rotation droite d'un noeud de l'AVL (pour l'équilibrage) (pour le -t)
pAvl_t doubleRotationDroite_t(pAvl_t monAvl){
	    monAvl->fg = rotationGauche_t(monAvl->fg);
        return rotationDroite_t(monAvl);
}

//Fonction qui équilibre un noeud de l'AVL (utilisation des rotations) (pour le -t)
pAvl_t equilibrerAVL_t(pAvl_t monAvl) {
    	if (monAvl == NULL){
        	return NULL;
    	}

    	if (monAvl->equilibre >= 2){
        	if (monAvl->fd != NULL && monAvl->fd->equilibre >= 0){
            		return rotationGauche_t(monAvl);
        	} 
        
        
        	else{
            		return doubleRotationGauche_t(monAvl);
    		} 
    	}
    	
    	else if (monAvl->equilibre <= -2) {
        	
        	if (monAvl->fg != NULL && monAvl->fg->equilibre <= 0) {
            		return rotationDroite_t(monAvl);
        	} 
        
        	else {
            		return doubleRotationDroite_t(monAvl);
        	}
    	}
    
    	return monAvl;
}

//Fonction qui ajoute un nouveau noeud dans un AVL (pour le -t)
pAvl_t ajoutAVL_t(pAvl_t monAvl, Ville maVille) {
    	if (monAvl == NULL) {
        	return creerArbre_t(maVille);
    	}

    	if (maVille.nb_fois < monAvl->elt.nb_fois) {
       	 	monAvl->fg = ajoutAVL_t(monAvl->fg, maVille);
    	} 
    	
    	else if (maVille.nb_fois >= monAvl->elt.nb_fois) {
        	monAvl->fd = ajoutAVL_t(monAvl->fd, maVille);
    	}
	
    	monAvl->equilibre = equilibre_t(monAvl);

    	return equilibrerAVL_t(monAvl);
}

// Fonction qui va lire les élément du csv créer en shell puis qui va insérer tous les éléments dans un AVL (pour le -t)
pAvl_t traitement(pAvl_t a){
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
        	a = ajoutAVL_t(a, ville);
    	}
    	
    	fclose(fichier);
	
	return a;	
}

//Fonction qui récupère les 10 villes les plus traversés dans l'AVL (pour le -t)
void infixeDecroissant10(pAvl_t monAvl, int* compteur, Ville tab[MAX_VILLE]) {
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

//Fonction qui libère la mémoire d'un noeud de l'AVL (pour le -t)
void libererAVL_t(pAvl_t monAvl){
	if(monAvl != NULL){
		libererAVL_t(monAvl->fg);
		libererAVL_t(monAvl->fd);
		free(monAvl);
	}
}

// Fonction qui échange deux éléments de type Ville (pour le -t)
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

// Fonction qui tri un tableau dans l'ordre alphabétique (pour le -t)
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

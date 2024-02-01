#include "all.h"

// main du programme C du traitement -t
int main(void){	
	//Initialisation des variables
	pAvl_t villeAVL = NULL;
	int c = 0;
	Ville tableau[MAX_VILLE];
	
	villeAVL = traitement(villeAVL); // utilisation de la fonction traitement, cela va remplir l'AVL des éléments contenu dans un fichier .csv 
	
	// Verififation de l'AVL donc verification du fonctionnement de la focntion traitement
	if(villeAVL == NULL){
		fprintf(stderr,"L'avl est vide !!!\n");
		exit(EXIT_FAILURE);
	}

	// Récupération des 10 villes les plus traversés dans l'AVL et remplissage du tableau par ces éléments
	infixeDecroissant10(villeAVL,&c,tableau);

	// Tri du tableau dans l'ordre alphabétique
	tri(tableau);

	// Affichage des éléments du tableau
	for(int i=0;i<MAX_VILLE;i++){
		printf("%s;%hu;%hu\n",tableau[i].nom,tableau[i].nb_fois,tableau[i].nb_depart);
	}

	// Libération de la mémoire alloué à l'AVL
	libererAVL_t(villeAVL);
		
	return 0;
}

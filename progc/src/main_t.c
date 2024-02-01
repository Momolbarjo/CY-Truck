#include "all.h"

// main du programme C du traitement -t
int main(void){
	pAvl_t villeAVL = NULL;
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
	
	libererAVL_t(villeAVL);
		
	return 0;
}

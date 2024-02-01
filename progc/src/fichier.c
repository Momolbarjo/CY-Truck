#include "all.h"

//https://winjia.medium.com/linux-getch-for-unix-c2c829721a30//
int getch(void) { 
    struct termios oldattr, newattr; 
    int ch; 
    tcgetattr(STDIN_FILENO, &oldattr); 
    newattr = oldattr; 
    newattr.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); 
    ch = getchar(); 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); 
    return ch; 
} 

Donnee extraireDonneeCSV(char *ligne) {
    Donnee donnee;
    char nombre_elem = sscanf(ligne, "%u\t%f\t%f\t%f\t%f", &donnee.id, &donnee.min, &donnee.max, &donnee.max_min, &donnee.moy);
    
    if (nombre_elem != 5) {
        fprintf(stderr, "Erreur, le/les types de données de votre fichier CSV ne sont pas adaptés\n");
        exit(EXIT_FAILURE);
    }
    return donnee;
}

void afficherAVLdansSortie(pAvl racine,FILE* sortie, int *n) {
    if (racine == NULL || *n == 0 || sortie == NULL) {
        return;
    }

    afficherAVLdansSortie(racine->fd,sortie, n);

    if (*n > 0) {
        fprintf(sortie,"%u:%f:%f:%f:%f\n", racine->donnee.id, racine->donnee.max_min, racine->donnee.max, racine->donnee.min, racine->donnee.moy);
        (*n)--;
    }

    afficherAVLdansSortie(racine->fg,sortie, n);
}

Ville extraireDonneeCSV_2(char *ligne) {
    	Ville ville;
    	
    	char nombre_elem = sscanf(ligne, "%[^,],%hu,%hu", ville.nom, &(ville.nb_fois), &(ville.nb_depart));
    	
    	if(nombre_elem != 3){
        	fprintf(stderr, "Erreur, le/les types de données de votre fichier CSV ne sont pas adaptés\n");
        	exit(EXIT_FAILURE);
    	}
    	
    	return ville;
}

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




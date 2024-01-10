#include "all.h"

int main(void) {

    FILE* entree = NULL;
    FILE* sortie = NULL;
    entree = fopen("temp/tmp_s1.csv","r");
    pAvl racine = construireAVL(entree);
    
    sortie = fopen("temp/tmp_s2.csv" , "w");
    
    if (sortie == NULL){
    	fprintf(stderr, "Erreur lors de l'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }


    int n = 50;
    afficherAVLdansSortie(racine,sortie, &n);

    
    fclose(sortie);
    // Libérer la mémoire allouée pour l'AVL
    libererMemoireAVL(racine);

    return 0;
}


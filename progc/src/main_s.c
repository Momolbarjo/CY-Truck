#include "all.h"

// main du programme C du traitement -s
int main(void) {

    //Initialisation des variables
    FILE* entree = NULL;
    FILE* sortie = NULL;
    entree = fopen("temp/tmp_s1.csv","r"); //Ouverture du fichier d'entrée

    //Verification de l'ouverture du fichier
    if (entree == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier d'entrée");
        exit(EXIT_FAILURE);
    }
    
    pAvl racine = construireAVL(entree); // Construction de l'AVL
    
    sortie = fopen("temp/tmp_s2.csv" , "w"); //Ouverture du fichier de sortie

    //Verification de l'ouverture du fichier
    if (sortie == NULL){
    	fprintf(stderr, "Erreur lors de l'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }


    int n = 50;
    afficherAVLdansSortie(racine,sortie, &n); // Affichage de 50 élément de l'AVL

    // Fermeture du fichier de sortie
    fclose(sortie);
    // Libérer la mémoire allouée pour l'AVL
    libererMemoireAVL(racine);

    return 0;
}


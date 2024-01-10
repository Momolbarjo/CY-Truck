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
    sscanf(ligne, "%u\t%f\t%f\t%f\t%f", &donnee.id, &donnee.min, &donnee.max, &donnee.max_min, &donnee.moy);
    return donnee;
}

void afficherAVLdansSortie(pAvl racine,FILE* sortie, int *n) {
    if (racine == NULL || *n == 0 || sortie == NULL) {
        return;
    }

    afficherAVLdansSortie(racine->fd,sortie, n);

    if (*n > 0) {
        fprintf(sortie,"id: %u, max_min: %f, max : %f, min : %f, moyenne : %f\n", racine->donnee.id, racine->donnee.max_min, racine->donnee.max, racine->donnee.min, racine->donnee.moy);
        (*n)--;
    }

    afficherAVLdansSortie(racine->fg,sortie, n);
}



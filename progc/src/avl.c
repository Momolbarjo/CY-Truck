#include "all.h"

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

char hauteur(pAvl monAvl) {
    if (monAvl != NULL) {
        return monAvl->hauteur;
    } else {
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

char equilibre(pAvl monAvl) {
    if (monAvl != NULL) {
        return hauteur(monAvl->fg) - hauteur(monAvl->fd);
    } else {
        return 0;
    }
}

pAvl doubleRotationGauche(pAvl myAvl) {
    myAvl->fd = rotationDroite(myAvl->fd);
    return rotationGauche(myAvl);
}

pAvl doubleRotationDroite(pAvl myAvl) {
    myAvl->fg = rotationGauche(myAvl->fg);
    return rotationDroite(myAvl);
}

pAvl equilibrerAVL(pAvl myAvl) {
    if (myAvl == NULL) {
        return NULL;
    }

    if (myAvl->equilibre >= 2) {
        if (myAvl->fd != NULL && myAvl->fd->equilibre >= 0) {
            return rotationGauche(myAvl);
        } else {
            return doubleRotationGauche(myAvl);
        }
    } else if (myAvl->equilibre <= -2) {
        if (myAvl->fg != NULL && myAvl->fg->equilibre <= 0) {
            return rotationDroite(myAvl);
        } else {
            return doubleRotationDroite(myAvl);
        }
    }
    return myAvl;
}

pAvl insererNoeudAVL(pAvl racine, Donnee donnee) {
    if (racine == NULL) {
        return creerArbre(donnee);
    }

    if (donnee.max_min < racine->donnee.max_min) {
        racine->fg = insererNoeudAVL(racine->fg, donnee);
    } else if (donnee.max_min > racine->donnee.max_min) {
        racine->fd = insererNoeudAVL(racine->fd, donnee);
    } else {
        return racine;
    }

    racine->equilibre = hauteur(racine->fg) - hauteur(racine->fd);

    return equilibrerAVL(racine);
}

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

void libererMemoireAVL(pAvl racine) {
    if (racine != NULL) {
        libererMemoireAVL(racine->fg);
        libererMemoireAVL(racine->fd);
        free(racine);
    }
}

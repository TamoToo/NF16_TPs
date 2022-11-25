#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main() {
    char choix;
    Parbre abr = NULL;
    char* nom = malloc(20*sizeof(char));
    char* prenom = malloc(20*sizeof(char));
    char* date, motif;
    do {
        fflush(stdin);
        afficherMenu();
        choix = getChoix();
        switch (choix) {
            case '1':
                printf("\t\tAjouter un patient\n");
                getNomPrenom(nom, prenom);
                printf("Nom : %s, Prenom : %s", nom, prenom);
                //inserer_patient(&abr, nom, prenom);
                break;
            case '2':
                printf("\t\tAjouter une consultation à un patient\n");
                break;
            case '3':
                printf("\t\tAfficher une fiche médicale\n");
                break;
            case '4':
                printf("\t\tAfficher la liste des patients\n");
                break;
            case '5':
                printf("\t\tSupprimer un patient\n");
                break;
            case '6':
                printf("\t\tCopier ou mettre à jour la liste des patients\n");
                break;
            case '7':
                printf("\t\tQuitter\n");
                break;
            default:
                printf("Choix incorrect\n");
        }
    } while (choix != '7');

    return 0;
}

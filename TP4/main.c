#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include <string.h>

#define MAX_LEN 20

int main() {
    char choix;
    Parbre abr = NULL;
    char nom[MAX_LEN];
    char prenom[MAX_LEN];
    char date[MAX_LEN];
    char motif[MAX_LEN];
    int nivu;
    do {
        fflush(stdin);
        afficherMenu();
        choix = getChoix();
        switch (choix) {
            case '1':
                printf("\t\tAjouter un patient\n");
                getNomPrenom(nom, MAX_LEN, "nom");
                getNomPrenom(prenom, MAX_LEN, "prénom");
                inserer_patient(&abr, nom, prenom);
                break;
            case '2':
                printf("\t\tAjouter une consultation à un patient\n");
                getNomPrenom(nom, MAX_LEN, "nom");
                getDate(date, MAX_LEN);
                getMotif(motif, MAX_LEN);
                getNivu(&nivu);
                ajouter_consultation(&abr, nom, date, motif, nivu);
                break;
            case '3':
                printf("\t\tAfficher une fiche médicale\n");
                getNomPrenom(nom, MAX_LEN, "nom");
                affiche_fiche(&abr, nom);
                break;
            case '4':
                printf("\t\tAfficher la liste des patients\n");
                afficher_patients(&abr);
                break;
            case '5':
                printf("\t\tSupprimer un patient\n");
                getNomPrenom(nom, MAX_LEN, "nom");
                supprimer_patient(&abr, nom);
                break;
            case '6':
                printf("\t\tCopier ou mettre à jour la liste des patients\n");
                break;
            case '7':
                printf("\t\tQuitter\n");
                supprimer_arbre(&abr);
                break;
            default:
                printf("Choix incorrect\n");
        }
    } while (choix != '7');

    return 0;
}

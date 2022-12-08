#include <stdio.h>
#include "tp4.h"

#define MAX_LEN 20

int main() {
    char choix;
    Parbre abr1 = NULL, abr2 = NULL;
    char nom[MAX_LEN], prenom[MAX_LEN], date[MAX_LEN], motif[MAX_LEN];
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
                inserer_patient(&abr1, nom, prenom);
                break;
            case '2':
                printf("\t\tAjouter une consultation à un patient\n");
                getNomPrenom(nom, MAX_LEN, "nom");
                getDate(date, MAX_LEN);
                getMotif(motif, MAX_LEN);
                getNivu(&nivu);
                ajouter_consultation(&abr1, nom, date, motif, nivu);
                break;
            case '3':
                printf("\t\tAfficher une fiche médicale\n");
                getNomPrenom(nom, MAX_LEN, "nom");
                affiche_fiche(&abr1, nom);
                break;
            case '4':
                printf("\t\tAfficher la liste des patients\n");
                afficher_patients(&abr1);
                break;
            case '5':
                printf("\t\tSupprimer un patient\n");
                getNomPrenom(nom, MAX_LEN, "nom");
                supprimer_patient(&abr1, nom);
                break;
            case '6':
                printf("\t\tCopier ou mettre à jour la liste des patients\n");
                break;
            case '7':
                printf("\t\tQuitter\n");
                supprimer_arbre(&abr1);
                supprimer_arbre(&abr2);
                break;
            default:
                printf("Choix incorrect\n");
        }
    } while (choix != '7');

    return 0;
}
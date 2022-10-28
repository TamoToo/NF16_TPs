#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"


// Liste chainée pour gérer plusieurs matrices creuses ??
//

int main() {

    int nb_matrice = getNbMatrice();
    int Nlignes, Ncolonnes;
    getSizeMatrice(&Nlignes, &Ncolonnes);
    matrice_creuse *M = malloc(nb_matrice * sizeof(matrice_creuse));
    int i, j;
    char choix;
    do{
        fflush(stdin);
        afficherMenu();
        choix = getChoix();
        switch(choix) {
            case '1':
                printf("Remplir une matrice creuse\n");
                i = getNumMatrice(nb_matrice);
                remplirMatrice(&M[i], Nlignes, Ncolonnes);
                break;
            case '2':
                printf("Afficher une matrice creuse sous forme de tableau\n");
                i = getNumMatrice(nb_matrice);
                afficherMatrice(M[i]);
                break;
            case '3':
                printf("Afficher une matrice creuse sous forme de listes\n");
                i = getNumMatrice(nb_matrice);
                afficherMatriceListes(M[i]);
                break;
            case '4':
                printf("Donner la valeur d'un élément d'une matrice creuse\n");
                break;
            case '5':
                printf("Affecter une valeur à un élément d'une matrice creuse\n");
                break;
            case '6':
                printf("Additioner deux matrices creuses\n");
                break;
            case '7':
                printf("Calculer le gain en espace en utilisant cette représentation pour une matrice donnée\n");
                break;
            case '8':
                printf("Quitter\n");
                break;
            default:
                printf("Choix incorrect\n");
        }
    }while(choix != '8');

    /*matrice_creuse M1,M2;
    remplirMatrice(&M1,2,2);
    remplirMatrice(&M2,2,2);
    afficherMatrice(M1);
    afficherMatrice(M2);
    afficherMatriceListes(M1);
    afficherMatriceListes(M2);
    additionerMatrices(M1,M2);
    afficherMatrice(M1);
    afficherMatriceListes(M1);*/
    return 0;
}

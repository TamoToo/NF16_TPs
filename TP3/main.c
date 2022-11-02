#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int main() {
    int nb_matrice = getNbMatrice();
    int Nlignes, Ncolonnes;
    getSizeMatrices(&Nlignes, &Ncolonnes);
    matrice_creuse *M = malloc(nb_matrice * sizeof(matrice_creuse));
    int num_matrice1, num_matrice2, i, j, val;
    char choix;
    do {
        fflush(stdin);
        afficherMenu();
        choix = getChoix();
        switch (choix) {
            case '1':
                printf("\t\tRemplir une matrice creuse\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                remplirMatrice(&M[num_matrice1], Nlignes, Ncolonnes);
                break;
            case '2':
                printf("\t\tAfficher une matrice creuse sous forme de tableau\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                afficherMatrice(M[num_matrice1]);
                break;
            case '3':
                printf("\t\tAfficher une matrice creuse sous forme de listes\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                afficherMatriceListes(M[num_matrice1]);
                break;
            case '4':
                printf("\t\tDonner la valeur d'un élément d'une matrice creuse\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                getLigneColonne(&i, &j, Nlignes, Ncolonnes);
                printf("La valeur de M%d[%d][%d] est : %d\n", num_matrice1, i, j, rechercherValeur(M[num_matrice1], i, j));
                break;
            case '5':
                printf("\t\tAffecter une valeur à un élément d'une matrice creuse\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                getLigneColonne(&i, &j, Nlignes, Ncolonnes);
                val = getValue();
                affecterValeur(M[num_matrice1], i, j, val);
                break;
            case '6':
                printf("\t\tAdditioner deux matrices creuses\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                num_matrice2 = getNumMatrice(nb_matrice);
                additionerMatrices(M[num_matrice1], M[num_matrice2]);
                break;
            case '7':
                printf("\t\tCalculer le gain en espace en utilisant cette représentation pour une matrice donnée\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                printf("Le nombre d'octets gagnés avec cette représentation pour la matrice M%d est de : %d octets\n", num_matrice1, nombreOctetsGagnes(M[num_matrice1]));
                break;
            case '8':
                printf("\t\tQuitter\n");
                for (int k = 0; k < nb_matrice; k++) {
                    if(M[k].Nlignes == Nlignes){ // Si la matrice a été remplie
                        libererMatrice(M[k]);
                    }
                }
                free(M);
                break;
            default:
                printf("Choix incorrect\n");
        }
    } while (choix != '8');

    return 0;
}
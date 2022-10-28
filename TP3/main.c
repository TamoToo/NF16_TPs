#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"


// Liste chainée pour gérer plusieurs matrices creuses ??
//

int main() {

    int nb_matrice = getNbMatrice();
    int Nlignes, Ncolonnes;
    getSizeMatrices(&Nlignes, &Ncolonnes);
    matrice_creuse *M = malloc(nb_matrice * sizeof(matrice_creuse));
    int num_matrice1, num_matrice2, i, j, val;
    char choix;
    do{
        fflush(stdin);
        afficherMenu();
        choix = getChoix();
        switch(choix) {
            case '1':
                printf("Remplir une matrice creuse\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                remplirMatrice(&M[num_matrice1], Nlignes, Ncolonnes);
                break;
            case '2':
                printf("Afficher une matrice creuse sous forme de tableau\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                afficherMatrice(M[num_matrice1]);
                break;
            case '3':
                printf("Afficher une matrice creuse sous forme de listes\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                afficherMatriceListes(M[num_matrice1]);
                break;
            case '4':
                printf("Donner la valeur d'un élément d'une matrice creuse\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                i = getLigne(Nlignes);
                j = getColonne(Ncolonnes);
                rechercherValeur(M[num_matrice1],i,j);
                break;
            case '5':
                printf("Affecter une valeur à un élément d'une matrice creuse\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                i = getLigne(Nlignes);
                j = getColonne(Ncolonnes);
                val = getValue();
                affecterValeur(M[num_matrice1], i, j, val);
                break;
            case '6':
                printf("Additioner deux matrices creuses\n");
                num_matrice1 = getNumMatrice(nb_matrice);
                num_matrice2 = getNumMatrice(nb_matrice);
                additionerMatrices(M[num_matrice1], M[num_matrice2]);
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
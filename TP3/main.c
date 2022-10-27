#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
#include <stdio.h>


int main() {
    int fin;
    fin = 0;
    while(!fin){
        int c;
        /* affichage menu */
        printf("1. Remplir une matrice creuse\n"
               "2. Afficher une matrice creuse sous forme de tableau\n"
               "3. Afficher une matrice creuse sous forme de listes\n"
               "4. Donner la valeur d'un élément d'une matrice creuse\n"
               "5. Affecter une valeur à un élément d'une matrice creuse\n"
               "6. Additioner deux matrices creuses\n"
               "7. Calculer le gain en espace en utilisant cette représentation pour une matrice donnée\n"
               "8. Quitter\n");
        c = getchar();
        /* suppression des caracteres dans stdin */
        if(c != '\n' && c != EOF){
            int d;
            while((d = getchar()) != '\n' && d != EOF);
        }
        matrice_creuse M1,M2;
        switch(c){
            case '1':
                printf("Remplir une matrice creuse\n");
                break;
            case '2':
                printf("Afficher une matrice creuse sous forme de tableau\n");
                break;
            case '3':
                printf("Afficher une matrice creuse sous forme de listes\n");
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
                fin = 1;
                printf("Quitter\n");
                break;
            default:
                printf("Choix errone\n");
        }
    }

    matrice_creuse M1,M2;
    remplirMatrice(&M1,2,2);
    remplirMatrice(&M2,2,2);
    afficherMatrice(M1);
    afficherMatrice(M2);
    afficherMatriceListes(M1);
    afficherMatriceListes(M2);
    additionerMatrices(M1,M2);
    afficherMatrice(M1);
    afficherMatriceListes(M1);
    return 0;
}

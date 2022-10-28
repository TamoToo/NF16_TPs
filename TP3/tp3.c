#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"



void afficherMenu(){
    printf("1. Remplir une matrice creuse\n"
           "2. Afficher une matrice creuse sous forme de tableau\n"
           "3. Afficher une matrice creuse sous forme de listes\n"
           "4. Donner la valeur d'un élément d'une matrice creuse\n"
           "5. Affecter une valeur à un élément d'une matrice creuse\n"
           "6. Additioner deux matrices creuses\n"
           "7. Calculer le gain en espace en utilisant cette représentation pour une matrice donnée\n"
           "8. Quitter\n");
}

char getChoix(){
    char c = getchar();
    /* suppression des caracteres dans stdin */
    fflush(stdin);
    return c;
}

// Récupère le nombre de matrices à gérer dans le programme
int getNbMatrice(){
    int n;
    printf("Combien de matrices comptez vous utiliser ? ");
    scanf("%d", &n);
    while(n <= 0){
        printf("Le nombre de matrices ne peut pas être négatif\n");
        printf("Veuillez rentrer un nombre strictement positif : ");
        scanf("%d", &n);
    }
    return n;
}

void getSizeMatrice(int *Nlignes, int *Ncolonnes){
    printf("Entrez le nombre de lignes des matrices à gérer : ");
    scanf("%d", Nlignes);
    printf("\nEntrez le nombre de colonnes des matrices à gérer : ");
    scanf("%d", Ncolonnes);
}

int getNumMatrice(int max){
    int n;
    printf("Quelle est le numéro de la matrice que vous voulez manipuler ? (0 - %d)", max-1);
    scanf("%d", &n);
    while(n >= max && n < 0){
        printf("Le nombre séléctionné est plus grand que le nombre total de matrices ou est négatif\n");
        printf("Veuillez rentrer un nouveau nombre :");
        scanf("%d", &n);
    }
    return n;
}

// Fonction qui permet de cr�er un �lement d'une liste cha�n�e
// Params : indice de colonne (int), valeur de l'�lement (int)
// Return : pointeur vers le nouvele �lement cr��
element *creerElement(int colonne, int valeur) {
    element *nouvelElement = malloc(sizeof(element));
    nouvelElement->col = colonne;
    nouvelElement->val = valeur;
    nouvelElement->suivant = NULL;
    return nouvelElement;
}

liste_ligne inserer_queue(element *e, liste_ligne l){
    if(l == NULL){
        return e;
    }
    element *tmp = l;
    while(tmp->suivant != NULL){
        tmp = tmp->suivant;
    }
    tmp->suivant = e;
    return l;
}


void remplirMatrice(matrice_creuse *m, int N, int M) {
    m->tab_lignes = malloc(N*sizeof(liste_ligne));
    m->Nlignes = N;
    m->Ncolonnes = M;
    int new_val;
    for(int i=0;i<N;i++){
        m->tab_lignes[i] = NULL;
        for(int j=0;j<M;j++){
            printf("Entrez l'entier [%d][%d] : ", i,j);
            scanf("%d", &new_val);
            if(new_val != 0){
                m->tab_lignes[i] = inserer_queue(creerElement(j,new_val),m->tab_lignes[i]);
            }
        }
    }
}


void afficherMatrice(matrice_creuse m){
    int Nlignes = m.Nlignes;
    int Ncolonnes = m.Ncolonnes;
    element *tmp = NULL;
    for(int i=0;i<Nlignes;i++){
        tmp = m.tab_lignes[i];
        for(int j=0;j<Ncolonnes;j++){
            if(tmp != NULL && tmp->col == j){
                printf("%d ", tmp->val);
                tmp = tmp->suivant;
            }
            else{
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void afficherMatriceListes(matrice_creuse m) {
    int Nlignes = m.Nlignes;
    element *tmp = NULL;
    for(int i=0;i<Nlignes;i++){
        tmp = m.tab_lignes[i];
        printf("Ligne %d : ",i);
        if(tmp == NULL){
            printf("*Ligne vide*");
        }
        while(tmp != NULL){
            printf("{%d %d} ", tmp->col, tmp->val);
            tmp = tmp->suivant;
        }
        printf("\n");
    }
}


int rechercherValeur(matrice_creuse m, int i, int j) {
    element *tmp = m.tab_lignes[i];
    while(tmp != NULL){
        if(tmp->col == j){
            return tmp->val;
        }
        tmp = tmp->suivant;
    }
    return 0;
}


void affecterValeur(matrice_creuse m, int i, int j, int val) {
    element *tmp = m.tab_lignes[i];
    element *tmp_prev = m.tab_lignes[i];
    element *new_elem = NULL;
    if(val != 0){
        if(tmp == NULL){ // aucun élement dans la ligne
            new_elem = creerElement(j,val);
            m.tab_lignes[i] = new_elem;
            new_elem->suivant = NULL;
        }
        else if (tmp->suivant == NULL){ // Si il n'y a qu'un seul élément dans la ligne
            if(j < tmp->col){
                new_elem = creerElement(j,val);
                m.tab_lignes[i] = new_elem;
                new_elem->suivant = tmp;
            }
            else if (j > tmp->col){
                new_elem = creerElement(j,val);
                tmp->suivant = new_elem;
                new_elem->suivant = NULL;
            }
            else{
                tmp->val = val;
            }
        }
        else{
            while(tmp != NULL && tmp->col < j){
                tmp_prev = tmp;
                tmp = tmp->suivant;
            }
            if(tmp == NULL) { // Si on est à la fin de la ligne (dernier element)
                new_elem = creerElement(j, val);
                tmp_prev->suivant = new_elem;
                new_elem->suivant = NULL;
            }
            else{
                if(tmp->col > j){
                    new_elem = creerElement(j,val);
                    tmp_prev->suivant = new_elem;
                    new_elem->suivant = tmp;
                }
                else{
                    tmp->val = val;
                }
            }
        }
    }
}


void additionerMatrices(matrice_creuse m1, matrice_creuse m2) {
    int Nlignes = m1.Nlignes;
    for(int i=0;i<Nlignes;i++){
        element *tmp1 = m1.tab_lignes[i];
        element *tmp2 = m2.tab_lignes[i];
        /* Tant qu'il y a des éléments dans les 2 listes, 3 cas se présentes :
            - 1 : la colonne de m1 > la colonne de m2 => val de m2 doit être ajoutée à m1 et on passe a la valeur suivante dans m2
            - 2 : les deux colonnes sont égales (les deux entiers se trouvent au même endroit) => on somme les deux entiers et on passe aux valeurs suivantes dans m1 et m2
            - 3 : la colonne de m1 < la colonne de m2 => on ne fait rien, on passe simplement à la prochaine valeur de m1
         */
        while(tmp1 != NULL && tmp2 != NULL){
            if(tmp1->col > tmp2->col){
                affecterValeur(m1, i,tmp2->col,tmp2->val);
                tmp2 = tmp2->suivant;
            }
            else if(tmp1->col == tmp2->col){
                affecterValeur(m1, i,tmp1->col, tmp1->val + tmp2->val);
                tmp1 = tmp1->suivant;
                tmp2 = tmp2->suivant;
            }
            else{
                tmp1 = tmp1->suivant;
            }
        }
        // Si on est sortie de la boucle précédente car tmp1 = NULL, il faut ajouter les valeurs restantes de tmp2 a tmp1.
        while(tmp2 != NULL){
            affecterValeur(m1, i,tmp2->col,tmp2->val);
            tmp2 = tmp2->suivant;
        }
    }
}


int nombreOctetsGagnes(matrice_creuse m) {

  /*Ecrire ici le code de cette fonction*/

}


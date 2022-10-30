#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"



void afficherMenu(){
    printf("\n\n1. Remplir une matrice creuse\n"
           "2. Afficher une matrice creuse sous forme de tableau\n"
           "3. Afficher une matrice creuse sous forme de listes\n"
           "4. Donner la valeur d'un élément d'une matrice creuse\n"
           "5. Affecter une valeur à un élément d'une matrice creuse\n"
           "6. Additioner deux matrices creuses\n"
           "7. Calculer le gain en espace en utilisant cette représentation pour une matrice donnée\n"
           "8. Quitter\n\n");
}

char getChoix(){
    char c = getchar();
    /* suppression des caracteres dans stdin */
    fflush(stdin);
    return c;
}

void isPositive(int *n){
    while(*n <= 0){
        printf("Le nombre ne peut pas être négatif\n");
        printf("Veuillez rentrer un nombre strictement positif : ");
        scanf("%d", n);
    }
}

void isBetween(int *n, int a, int b){
    while(*n < a || *n > b){
        printf("Le nombre doit être compris entre %d et %d", a,b);
        printf("Veuillez rentrez un nouveau nombre : ");
        scanf("%d", n);
    }
}

// Récupère le nombre de matrices à gérer dans le programme
int getNbMatrice(){
    int n;
    printf("Combien de matrices comptez vous utiliser ? ");
    scanf("%d", &n);
    isPositive(&n);
    return n;
}

void getSizeMatrices(int *Nlignes, int *Ncolonnes){
    printf("Entrez le nombre de lignes des matrices à gérer : ");
    scanf("%d", Nlignes);
    isPositive(Nlignes);
    printf("\nEntrez le nombre de colonnes des matrices à gérer : ");
    scanf("%d", Ncolonnes);
    isPositive(Ncolonnes);
}

int getNumMatrice(int max){
    int n;
    printf("Quel est le numéro de la matrice que vous voulez manipuler ? [0 - %d]", max-1);
    scanf("%d", &n);
    isBetween(&n,0,max);
    return n;
}

int getLigne(int max){
    int i;
    printf("Quel est le numéro de la ligne que vous voulez ?");
    scanf("%d", &i);
    isBetween(&i,0,max-1);
    return i;
}

int getColonne(int max){
    int j;
    printf("Quel est le numéro de la colonne que vous voulez ?");
    scanf("%d", &j);
    isBetween(&j,0,max-1);
    return j;
}

int getValue(){
    int val;
    printf("Quelle valeur voulez-vous insérer ? ");
    scanf("%d", &val);
    return val;
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

liste_ligne inserer_tete(element *e, liste_ligne l){
    e->suivant = l;
    return e;
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

void libererMatrice(matrice_creuse m){
    element *tmp;
    element *free_tmp;
    for (int i=0; i<m.Nlignes; i++){
        tmp = m.tab_lignes[i];
        while(tmp != NULL){
            free_tmp = tmp;
            tmp = tmp->suivant;
            free(free_tmp);
        }
        free(m.tab_lignes[i]);
    }
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
        if(tmp->col == j){ // Si on trouve la valeur dans la ligne i on la renvoie
            return tmp->val;
        }
        tmp = tmp->suivant;
    }
    return 0; // Sinon, on renvoie 0 par défaut
}


void affecterValeur(matrice_creuse m, int i, int j, int val) {
    element *tmp = m.tab_lignes[i];
    element *tmp_prev = m.tab_lignes[i];
    element *new_elem = NULL;
    int prev_val = rechercherValeur(m, i, j);
    if(prev_val == val){
        return;
    }
    if(prev_val == 0){ // val != 0 --> Insérer un nouveau élément
        if(tmp == NULL || j < tmp->col){ // Aucun élément dans la ligne OU élément à insérer en tête
            m.tab_lignes[i] = inserer_tete(creerElement(j,val), m.tab_lignes[i]);
        }
        else{
            while(tmp != NULL && j > tmp->col){
                tmp_prev = tmp;
                tmp = tmp->suivant;
            }
            /* On verifie la condition de sortie de la boucle:
             * tmp = NULL --> on est arrivé au bout de la liste
             * j > col --> on doit insérer l'élement à cette position
             */
            if(tmp == NULL){
                m.tab_lignes[i] = inserer_queue(creerElement(j,val), m.tab_lignes[i]);
            }
            else{
                new_elem = creerElement(j, val);
                tmp_prev->suivant = new_elem;
                new_elem->suivant = tmp;
            }
        }
        return;
    }
    // prev_val != 0 --> L'élément que l'on cherche à modifier EXISTE TOUJOURS
    while(j != tmp->col){
        tmp_prev = tmp;
        tmp = tmp->suivant;
    }
    if(val == 0){ // Supprimer un élément
        if(tmp == tmp_prev){ // Si l'élément a supprimé est le premier de la liste
            m.tab_lignes[i] = tmp->suivant;
        }
        else{
            tmp_prev->suivant = tmp->suivant;
        }
        free(tmp);
        return;
    }
    // On change simplement l'ancienne valeur par la nouvelle (!=0)
    tmp->val = val;
}


void additionerMatrices(matrice_creuse m1, matrice_creuse m2) {
    int Nlignes = m1.Nlignes;
    for(int i=0;i<Nlignes;i++){
        element *tmp1 = m1.tab_lignes[i];
        element *tmp1_prev = m1.tab_lignes[i];
        element *tmp2 = m2.tab_lignes[i];
        element *new_elem = NULL;
        /* Tant qu'il y a des éléments dans les 2 listes, 3 cas se présentent :
            - 1 : la colonne de m1 > la colonne de m2 => val de m2 doit être ajoutée à m1 et on passe a la valeur suivante dans m2
            - 2 : les deux colonnes sont égales (les deux entiers se trouvent au même endroit) => on somme les deux entiers et on passe aux valeurs suivantes dans m1 et m2
            - 3 : la colonne de m1 < la colonne de m2 => on ne fait rien, on passe simplement à la prochaine valeur de m1
         */
        while(tmp1 != NULL && tmp2 != NULL){
            if(tmp1->col > tmp2->col){
                new_elem = creerElement(tmp2->col, tmp2->val);
                if(tmp1 == tmp1_prev){ // S'il n'y a aucun élément dans la ligne de m1 (tmp1 = tmp1_prev = NULL), on insère le nouveau élément en tête de la liste de m1
                    m1.tab_lignes[i] =  inserer_tete(new_elem, m1.tab_lignes[i]);
                }
                else{
                    new_elem->suivant = tmp1;
                    tmp1_prev->suivant = new_elem;
                }
                tmp2 = tmp2->suivant;
            }
            else if(tmp1->col == tmp2->col){
                tmp1->val += tmp2->val;
                tmp1_prev = tmp1;
                tmp1 = tmp1->suivant;
                tmp2 = tmp2->suivant;
            }
            else{
                tmp1_prev = tmp1;
                tmp1 = tmp1->suivant;
            }
        }
        // Si on est sortie de la boucle précédente car tmp1 = NULL, il faut ajouter les valeurs restantes de tmp2 a tmp1.
        if(tmp1 == NULL){
            if(tmp1 == tmp1_prev){ // S'il n'y a aucun élément dans la ligne de m1 (tmp1 = tmp1_prev = NULL)
                m1.tab_lignes[i] =  m2.tab_lignes[i];
            }
            else{
                tmp1_prev->suivant = tmp2;
            }
        }
    }
}


int nombreOctetsGagnes(matrice_creuse m) {
    int res = 0;
    element *tmp;
    for (int i=0; i<m.Nlignes; i++){
        tmp = m.tab_lignes[i];
        while(tmp != NULL){
            res++;
            tmp = tmp->suivant;
        }
    }
    res *= sizeof(element); // taille de tous les noeuds représentés
    res += m.Nlignes * sizeof(liste_ligne); // taille de tous les noeuds + toutes les lignes
    res += sizeof(matrice_creuse); // taille de tous les noeuds + toutes les lignes + taille d'une matrice
    res = m.Ncolonnes * m.Nlignes * sizeof(int) - res; // N*M*taille d'un entier - taille de notre représentation
    return res;
}


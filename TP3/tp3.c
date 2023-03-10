#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

void afficherMenu() {
    printf("\n\n\t\t\tMENU\n"
           "1. Remplir une matrice creuse\n"
           "2. Afficher une matrice creuse sous forme de tableau\n"
           "3. Afficher une matrice creuse sous forme de listes\n"
           "4. Donner la valeur d'un élément d'une matrice creuse\n"
           "5. Affecter une valeur à un élément d'une matrice creuse\n"
           "6. Additioner deux matrices creuses\n"
           "7. Calculer le gain en espace en utilisant cette représentation pour une matrice donnée\n"
           "8. Quitter\n\n"
           "Choix : ");
}

void isPositive(int *n) {
    while (*n <= 0) {
        printf("Le nombre ne peut pas être négatif ou nul\n");
        printf("Veuillez rentrer un nombre strictement positif : ");
        scanf("%d", n);
    }
}

void isBetween(int *n, int a, int b) {
    while (*n < a || *n > b) {
        printf("Le nombre doit être compris entre %d et %d\n", a, b);
        printf("Veuillez rentrez un nouveau nombre : ");
        scanf("%d", n);
    }
}

char getChoix() {
    char c = getchar();
    /* suppression des caracteres dans stdin */
    fflush(stdin);
    return c;
}

// Récupère le nombre de matrices à gérer dans le programme
int getNbMatrice() {
    int n;
    printf("\nCombien de matrices comptez vous utiliser ? ");
    scanf("%d", &n);
    isPositive(&n);
    return n;
}

// Récupère la taille des matrices à gérer dans le programme
void getSizeMatrices(int *Nlignes, int *Ncolonnes) {
    printf("\nEntrez le nombre de lignes des matrices à gérer : ");
    scanf("%d", Nlignes);
    isPositive(Nlignes);
    printf("\nEntrez le nombre de colonnes des matrices à gérer : ");
    scanf("%d", Ncolonnes);
    isPositive(Ncolonnes);
}

// Récupère le numéro de la matrice que l'on cherche à manipuler
int getNumMatrice(int max) {
    int n;
    printf("\nQuel est le numéro de la matrice que vous voulez manipuler ? [0 - %d] ", max - 1);
    scanf("%d", &n);
    isBetween(&n, 0, max - 1);
    return n;
}

// Récupère le numéro de la ligne et de la colonne de la matrice que l'on cherche à manipuler
void getLigneColonne(int *i, int *j, int maxL, int maxC) {
    printf("\nQuel est le numéro de la ligne que vous voulez ? ");
    scanf("%d", i);
    isBetween(i, 0, maxL - 1);
    printf("\nQuel est le numéro de la colonne que vous voulez ? ");
    scanf("%d", j);
    isBetween(j, 0, maxC - 1);
}

// Récupère la valeur que l'on veut insérer dans la fonction affecterValeur
int getValue() {
    int val;
    printf("\nQuelle valeur voulez-vous insérer ? ");
    scanf("%d", &val);
    return val;
}

// Insère un élément en tête d'une liste_ligne
liste_ligne inserer_tete(element * e, liste_ligne l) {
    e->suivant = l;
    return e;
}

// Libère la mémoire d'une matrice creuse
void libererMatrice(matrice_creuse m) {
    element *tmp;
    element *free_tmp;
    for (int i = 0; i < m.Nlignes; i++) {
        tmp = m.tab_lignes[i];
        while (tmp != NULL) {
            free_tmp = tmp;
            tmp = tmp->suivant;
            free(free_tmp);
        }
    }
    free(m.tab_lignes);
}

// Fonction qui permet de cr�er un �lement d'une liste cha�n�e
// Params : indice de colonne (int), valeur de l'�lement (int)
// Return : pointeur vers le nouvele �lement cr��
element *creerElement(int colonne, int valeur) {
    element * nouvelElement = malloc(sizeof(element));
    nouvelElement->col = colonne;
    nouvelElement->val = valeur;
    nouvelElement->suivant = NULL;
    return nouvelElement;
}

void remplirMatrice(matrice_creuse *m, int N, int M) {
    m->tab_lignes = malloc(N * sizeof(liste_ligne)); // realloc pour éviter de ré-allouer de l'espace lorsque l'on modifie une matrice déja créer ?
    m->Nlignes = N;
    m->Ncolonnes = M;
    element *new_elem, *tmp;
    int val;
    for (int i = 0; i < N; i++) {
        m->tab_lignes[i] = NULL;
        tmp = NULL;
        for (int j = 0; j < M; j++) {
            printf("\nEntrez l'entier [%d][%d] : ", i, j);
            scanf("%d", &val);
            if (val != 0) {
                new_elem = creerElement(j, val);
                if (m->tab_lignes[i] == NULL){
                    m->tab_lignes[i] = new_elem;
                    tmp = new_elem;
                } else{
                    tmp->suivant = new_elem;
                    tmp = tmp->suivant;
                }
            }
        }
    }
}

void afficherMatrice(matrice_creuse m) {
    element *tmp = NULL;
    printf("\n\n");
    for (int i = 0; i < m.Nlignes; i++) {
        tmp = m.tab_lignes[i];
        for (int j = 0; j < m.Ncolonnes; j++) {
            if (tmp != NULL && tmp->col == j) {
                printf("%d ", tmp->val);
                tmp = tmp->suivant;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void afficherMatriceListes(matrice_creuse m) {
    element *tmp = NULL;
    printf("\n\n");
    for (int i = 0; i < m.Nlignes; i++) {
        tmp = m.tab_lignes[i];
        printf("Ligne %d : ", i);
        if (tmp == NULL) {
            printf("*Ligne vide*");
        }
        while (tmp != NULL) {
            printf("{%d %d} ", tmp->col, tmp->val);
            tmp = tmp->suivant;
        }
        printf("\n");
    }
}

int rechercherValeur(matrice_creuse m, int i, int j) {
    element *tmp = m.tab_lignes[i];
    while (tmp != NULL && tmp->col <= j) { // la condition "tmp->col <= j" permet d'éviter de parcourir toute la liste dans certains cas
        if (tmp->col == j) return tmp->val; // Si on trouve la valeur dans la ligne i on la renvoie
        tmp = tmp->suivant;
    }
    return 0; // Sinon, on renvoie 0 par défaut
}

void affecterValeur(matrice_creuse m, int i, int j, int val) {
    element *tmp = m.tab_lignes[i];
    element *tmp_prev = m.tab_lignes[i];
    element *new_elem = NULL;
    int prev_val = rechercherValeur(m, i, j);
    if (prev_val == val) return;
    if (prev_val == 0) { // val != 0 --> Insérer un nouveau élément
        if (tmp == NULL || j < tmp->col) { // Aucun élément dans la ligne OU élément à insérer en tête
            m.tab_lignes[i] = inserer_tete(creerElement(j, val), m.tab_lignes[i]);
        } else {
            while (tmp != NULL && j > tmp->col) {
                tmp_prev = tmp;
                tmp = tmp->suivant;
            }
             /* tmp = NULL --> on est arrivé au bout de la liste => on insère l'élément en dernier
             * j > col --> on doit insérer l'élement à cette position
             */
            new_elem = creerElement(j, val);
            tmp_prev->suivant = new_elem;
            new_elem->suivant = tmp;
        }
        return;
    }
    // SINON, prev_val != 0 --> L'élément que l'on cherche à modifier EXISTE TOUJOURS
    while (j != tmp->col) {
        tmp_prev = tmp;
        tmp = tmp->suivant;
    }
    if (val == 0) { // Supprimer un élément
        if (tmp == tmp_prev) { // Si l'élément a supprimé est le premier de la liste
            m.tab_lignes[i] = tmp->suivant;
        } else {
            tmp_prev->suivant = tmp->suivant;
        }
        free(tmp);
        return;
    }
    // val !=0 --> On change simplement l'ancienne valeur par la nouvelle (!=0)
    tmp->val = val;
}

void additionerMatrices(matrice_creuse m1, matrice_creuse m2) {
    element *tmp1, *tmp1_prev, *tmp2, *new_elem;
    int sum;
    for (int i = 0; i < m1.Nlignes; i++) {
        tmp1 = m1.tab_lignes[i];
        tmp1_prev = m1.tab_lignes[i];
        tmp2 = m2.tab_lignes[i];
        /* Tant qu'il y a des éléments dans les 2 listes, 3 cas se présentent :
            - 1 : la colonne de m1 > la colonne de m2 => val de m2 doit être ajoutée à m1 et on passe a la valeur suivante dans m2
            - 2 : les deux colonnes sont égales (les deux entiers se trouvent au même endroit) => on somme les deux entiers --> si la somme vaut 0, on doit supprimer le noeud, sinon, on passe simplement aux valeurs suivantes dans m1 et m2
            - 3 : la colonne de m1 < la colonne de m2 => on ne fait rien, on passe simplement à la prochaine valeur de m1
         */
        while (tmp1 != NULL && tmp2 != NULL) {
            if (tmp1->col > tmp2->col) {
                new_elem = creerElement(tmp2->col, tmp2->val);
                if (tmp1 == tmp1_prev) { // Si c'est le premier élément de m1, on insère le nouvel élément en tête de la liste de m1
                    m1.tab_lignes[i] = inserer_tete(new_elem, m1.tab_lignes[i]);
                    tmp1_prev = m1.tab_lignes[i];
                } else {
                    new_elem->suivant = tmp1;
                    tmp1_prev->suivant = new_elem;
                    tmp1_prev = tmp1_prev->suivant;
                }
                tmp2 = tmp2->suivant;
            } else if (tmp1->col == tmp2->col) {
                sum = tmp1->val + tmp2->val;
                if(sum == 0){
                    if(tmp1 == tmp1_prev){ // Si c'est le premier élément de m1
                        tmp1 = tmp1->suivant;
                        free(tmp1_prev);
                        tmp1_prev = tmp1;
                        m1.tab_lignes[i] = tmp1;
                    } else{
                        tmp1_prev->suivant = tmp1->suivant;
                        free(tmp1);
                        tmp1 = tmp1_prev->suivant;
                    }
                } else{
                    tmp1->val = sum;
                    tmp1_prev = tmp1;
                    tmp1 = tmp1->suivant;
                }
                tmp2 = tmp2->suivant;
            } else {
                tmp1_prev = tmp1;
                tmp1 = tmp1->suivant;
            }
        }
        // Si on est sortie de la boucle précédente car tmp1 = NULL, il faut ajouter les valeurs restantes de tmp2 a tmp1
        // Sinon on a fini car les valeurs restantes sont déjà présentes dans m1
        if (tmp1 == NULL) {
            if (tmp1 == tmp1_prev) { // S'il n'y a aucun élément dans la ligne de m1 (tmp1 = tmp1_prev = NULL), la ligne de m1 = la ligne de m2
                m1.tab_lignes[i] = tmp2;
            } else { // Sinon, on ajoute la suite de la liste de m2 au suivant du précédent de tmp1
                tmp1_prev->suivant = tmp2;
            }
        }
    }
}

int nombreOctetsGagnes(matrice_creuse m) {
    int res = 0;
    element *tmp = NULL;
    for (int i = 0; i < m.Nlignes; i++) {
        tmp = m.tab_lignes[i];
        while (tmp != NULL) {
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
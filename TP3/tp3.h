#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED


// STRUCTURE ELEMENT
typedef struct Element {
    int col;
    int val;
    struct Element *suivant;
}element;

// TYPE LISTE_LIGNE
typedef element *liste_ligne;


// STRUCTURE MATRICE CREUSE
typedef struct MatriceCreuse {
    int Nlignes;
    int Ncolonnes;
    liste_ligne *tab_lignes;
}matrice_creuse;


void remplirMatrice(matrice_creuse *m, int N, int M);
void afficherMatrice(matrice_creuse m);
void afficherMatriceListes(matrice_creuse m);
int rechercherValeur(matrice_creuse m, int i, int j);
void affecterValeur(matrice_creuse m, int i, int j, int val);
void additionerMatrices(matrice_creuse m1, matrice_creuse m2);
int nombreOctetsGagnes(matrice_creuse m);
void afficherMenu();
char getChoix();
void isPositive(int *n);
void isBetween(int *n, int a, int b);
int getNbMatrice();
void getSizeMatrices(int *Nlignes, int *Ncolonnes);
int getNumMatrice(int max);
int getLigne(int max);
int getColonne(int max);
int getValue();

#endif // TP3_H_INCLUDED

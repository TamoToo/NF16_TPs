#ifndef TP4_TP4_H
#define TP4_TP4_H

typedef struct Consultation{
    char* date;
    char *motif;
    int niveauUrg;
    struct Consultation* suivant;
}Consultation;

typedef struct Patient{
    char* nom;
    char* prenom;
    Consultation* ListConsult;
    int nbrconsult;
    struct Patient* fils_gauche;
    struct Patient* fils_droit;
}Patient;

typedef Patient* Parbre;

void afficherMenu();
char getChoix();
void getNomPrenom(char* nom, char* prenom);
Patient* CreerPatient(char* nm, char* pr);
void inserer_patient(Parbre* abr, char* nm, char* pr);
Patient* rechercher_patient(Parbre* abr, char* nm);
void affiche_fiche(Parbre* abr, char* nm);
void afficher_patients(Parbre* abr);
Consultation* CreerConsult(char* date, char* motif, int nivu);
void ajouter_consultation(Parbre* abr, char* nm, char* date, char* motif, int nivu);
void supprimer_patient(Parbre* abr, char *nm);

#endif //TP4_TP4_H

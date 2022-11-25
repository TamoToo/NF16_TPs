#include "tp4.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void afficherMenu() {
    printf("\n\n\t\t\tMENU\n"
           "1. Ajouter un patient\n"
           "2. Ajouter une consultation à un patient\n"
           "3. Afficher une fiche médicale\n"
           "4. Afficher la liste des patients\n"
           "5. Supprimer un patient\n"
           "6. Copier ou mettre à jour la liste des patients\n"
           "7. Quitter\n\n"
           "Choix : ");
}

char getChoix() {
    char c = getchar();
    /* suppression des caracteres dans stdin */
    fflush(stdin);
    return c;
}

char* strtoupper(char* dest, const char* src){
    char* result = dest;
    while( *dest++ = toupper(*src++) );
    return result;
}

void getNomPrenom(char* nom, char* prenom){
    int i = 0;
    printf("\nVeuillez entrez votre nom : ");
    fgets(nom, 20, stdin);
    printf("\nVeuillez entrez votre prénom : ");
    fgets(prenom, 20, stdin);
}


Patient* CreerPatient(char* nm, char* pr) {
    Patient* new_patient = (Patient*)malloc(sizeof(Patient));
    if (new_patient == NULL) return NULL;
    new_patient->nom = nm;
    new_patient->prenom = pr;
    new_patient->ListConsult = NULL;
    new_patient->nbrconsult = 0;
    new_patient->fils_gauche = NULL;
    new_patient->fils_droit = NULL;
}

void inserer_patient(Parbre* abr, char* nm, char* pr) {
    Patient* tmp = (*abr);
    while(tmp != NULL && strcmp(tmp->nom, nm) != 0) {
        if(strcmp(tmp->nom, nm) > 0) {
            tmp = tmp->fils_gauche;
        } else {
            tmp = tmp->fils_droit;
        }
    }
    if(tmp == NULL) {
        tmp = CreerPatient(nm, pr);
        return;
    }
    printf("\nLe patient est déjà présent dans l'arbre");

}

Patient* rechercher_patient(Parbre* abr, char* nm) {
    Patient* tmp = (*abr);
    while(tmp != NULL){
        if(strcmp(tmp->nom, nm) == 0) return tmp;
        if(strcmp(tmp->nom, nm) > 0) {
            tmp = tmp->fils_gauche;
        } else {
            tmp = tmp->fils_droit;
        }
    }
    printf("\nLe patient n'a pas été trouvé");
}

void affiche_fiche(Parbre* abr, char* nm) {
    Patient* patient = rechercher_patient(abr, nm);
    Consultation* tmp = patient->ListConsult;
    printf("\nNom : %s", patient->nom);
    printf("\nPrenom : %s", patient->prenom);
    printf("\nNombre de consultations : %d", patient->nbrconsult);
    while(tmp != NULL){
        printf("\nDate : %s", tmp->date);
        printf("\nMotif : %s", tmp->motif);
        printf("\nNiveau d'Urgence : %d", tmp->niveauUrg);
        tmp = tmp->suivant;
    }
}

void afficher_patients(Parbre* abr) {
    if(*abr == NULL) return;
    printf("\n%s", (*abr)->nom);
    afficher_patients(&(*abr)->fils_gauche);
    afficher_patients(&(*abr)->fils_droit);
}

Consultation* CreerConsult(char* date, char* motif, int nivu) {
    Consultation* new_consult = (Consultation*) malloc(sizeof(Consultation));
    if(new_consult == NULL) return NULL;
    new_consult->date = date;
    new_consult->motif = motif;
    new_consult->niveauUrg = nivu;
    return new_consult;
}

void ajouter_consultation(Parbre* abr, char* nm, char* date, char* motif, int nivu) {
    Patient* patient = rechercher_patient(abr, nm);
    Consultation* tmp = patient->ListConsult;
    Consultation* tmp_prev;
    if(patient == NULL){
        printf("\nLe patient n'existe pas");
        return;
    }
    while(tmp != NULL && strcmp(tmp->date, date) < 0) {
        tmp_prev = tmp;
        tmp = tmp->suivant;
    }
    patient->nbrconsult++;
    tmp_prev->suivant = CreerConsult(date, motif, nivu);
    if(tmp == NULL) return; // Ajouter en fin de liste
    tmp_prev->suivant->suivant = tmp; // Ajouter au milieu de la liste
}

void supprimer_patient(Parbre* abr, char *nm){
    if(*abr == NULL){
        printf("\nIl n'existe aucun patient dans l'arbre");
        return;
    }
    Patient* patient = rechercher_patient(abr, nm);
    if (patient == NULL){
        printf("Le patient n'exsite pas");
        return;
    }

}



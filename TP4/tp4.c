#include "tp4.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>
#include <time.h>

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


void getNomPrenom(char* str, int max_size, char* type){
    printf("\nVeuillez entrez le %s du patient: ", type);
    fgets(str, max_size, stdin);
    while(*str) {
        if ( *str >= 'a' && *str <= 'z' ) {
            *str = *str - 32;
        }
        str++;
    }
}

void getDate(char* date, int max_size){
    int day, month, year;
    printf("\nQuelle est la date de la consultation (JJ-MM-AAAA) ? : ");
    fgets(date, max_size, stdin);
    while(sscanf(date, "%2d-%2d-%4d", &day, &month, &year) != 3){
        printf("\nLe format est incorrect, veuillez réessayer : ");
        fgets(date, max_size, stdin);
    }
}

void getMotif(char* motif, int max_size){
    printf("\nQuel est le motif de la consultation ? : ");
    fgets(motif, max_size, stdin);
}

void getNivu(int* nivu){ // On suppose que le niveau d'urgence doit être compris entre 1 et 5
    printf("\nQuelle est le niveau d'urgence de la consutlation (1-5) ? : ");
    scanf("%d", nivu);
    while(*nivu < 1 || *nivu > 5){
        printf("\nNiveau d'urgence incorrect, veuillez réessayer : ");
        scanf("%d", nivu);
    }
}


Patient* CreerPatient(char* nm, char* pr) {
    Patient* new_patient = (Patient*)malloc(sizeof(Patient));
    if (new_patient == NULL) return NULL;
    new_patient->nom = malloc(sizeof(nm));
    strcpy(new_patient->nom, nm);
    new_patient->prenom = malloc(sizeof(pr));
    strcpy(new_patient->prenom, pr);
    new_patient->ListConsult = NULL;
    new_patient->nbrconsult = 0;
    new_patient->fils_gauche = NULL;
    new_patient->fils_droit = NULL;
}

void inserer_patient(Parbre* abr, char* nm, char* pr) {
    Patient* tmp = (*abr);
    Patient* tmp_prev = NULL;
    while(tmp != NULL) {
        if (strcmp(tmp->nom, nm) < 0) {
            tmp_prev = tmp;
            tmp = tmp->fils_droit;
        }
        else if (strcmp(tmp->nom, nm) > 0) {
            tmp_prev = tmp;
            tmp = tmp->fils_gauche;
        }
        else {
            printf("\nLe patient existe déjà");
            return;
        }
    }
    tmp = CreerPatient(nm, pr);
    if(tmp_prev != NULL) {
        if (strcmp(tmp_prev->nom, nm) < 0) tmp_prev->fils_droit = tmp;
        else tmp_prev->fils_gauche = tmp;
        return;
    }
    *abr = CreerPatient(nm, pr);
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
    int i = 1;
    Patient* patient = rechercher_patient(abr, nm);
    Consultation* tmp = patient->ListConsult;
    printf("\nNom : %s", patient->nom);
    printf("\nPrenom : %s", patient->prenom);
    printf("\nNombre de consultations : %d", patient->nbrconsult);
    while(tmp != NULL){
        printf("\nConsultation n°%d:", i);
        printf("\n\tDate : %s", tmp->date);
        printf("\n\tMotif : %s", tmp->motif);
        printf("\n\tNiveau d'Urgence : %d", tmp->niveauUrg);
        tmp = tmp->suivant;
        i++;
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
    new_consult->date = malloc(sizeof(date));
    strcpy(new_consult->date, date);
    new_consult->motif = malloc(sizeof(motif));
    strcpy(new_consult->motif, motif);
    new_consult->niveauUrg = nivu;
    new_consult->suivant = NULL;
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
    patient->nbrconsult++;
    if(tmp == NULL){
        printf("HERE");
        patient->ListConsult = CreerConsult(date, motif, nivu);
        return;
    }
    while(tmp != NULL && strcmp(tmp->date, date) < 0) {
        tmp_prev = tmp;
        tmp = tmp->suivant;
    }
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



#include "tp4.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void getNomPrenom (char* str, int max_size, char* type) {
    printf("\nVeuillez entrez le %s du patient: ", type);
    fgets(str, max_size, stdin);
    while (*str) {
        if ( *str >= 'a' && *str <= 'z' ) {
            *str = *str - 32;
        }
        str++;
    }
}

void getDate (char* date, int max_size) {
    int day, month, year;
    printf("\nQuelle est la date de la consultation (JJ-MM-AAAA) ? : ");
    fgets(date, max_size, stdin);
    while (sscanf(date, "%2d-%2d-%4d", &day, &month, &year) != 3) {
        printf("\nLe format est incorrect, veuillez réessayer : ");
        fgets(date, max_size, stdin);
    }
}

void getMotif (char* motif, int max_size) {
    printf("\nQuel est le motif de la consultation ? : ");
    fgets(motif, max_size, stdin);
}

void getNivu (int* nivu) { // On suppose que le niveau d'urgence doit être compris entre 1 et 5
    printf("\nQuelle est le niveau d'urgence de la consutlation (1-5) ? : ");
    scanf("%d", nivu);
    while (*nivu < 1 || *nivu > 5) {
        printf("\nNiveau d'urgence incorrect, veuillez réessayer : ");
        scanf("%d", nivu);
    }
}

Patient* CreerPatient (char* nm, char* pr) {
    Patient* new_patient = (Patient*)malloc(sizeof(Patient));
    if (new_patient == NULL) return NULL;
    new_patient->nom = malloc(sizeof(char) * (strlen(nm) + 1));
    if (new_patient->nom == NULL) return NULL;
    strcpy(new_patient->nom, nm);
    new_patient->prenom = malloc(sizeof(char) * (strlen(pr) + 1));
    if (new_patient->prenom == NULL) return NULL;
    strcpy(new_patient->prenom, pr);
    new_patient->ListConsult = NULL;
    new_patient->nbrconsult = 0;
    new_patient->fils_gauche = NULL;
    new_patient->fils_droit = NULL;
    return new_patient;
}

void inserer_patient (Parbre* abr, char* nm, char* pr) {
    Patient* tmp = (*abr);
    Patient* tmp_prev = NULL;
    while (tmp != NULL) {
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
    if (tmp_prev != NULL) {
        if (strcmp(tmp_prev->nom, nm) < 0) tmp_prev->fils_droit = tmp;
        else tmp_prev->fils_gauche = tmp;
    }
    else *abr = tmp;
}

Patient* rechercher_patient (Parbre* abr, char* nm) {
    Patient* tmp = (*abr);
    while (tmp != NULL){
        if(strcmp(tmp->nom, nm) == 0) return tmp;
        if(strcmp(tmp->nom, nm) > 0) {
            tmp = tmp->fils_gauche;
        } else {
            tmp = tmp->fils_droit;
        }
    }
    printf("\nLe patient n'a pas été trouvé");
    return NULL;
}

void affiche_fiche (Parbre* abr, char* nm) {
    int i = 1;
    Patient* patient = rechercher_patient(abr, nm);
    if (patient == NULL) return;
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

void afficher_patients (Parbre* abr) {
    if (*abr == NULL) return;
    printf("\nNom : %s", (*abr)->nom);
    afficher_patients(&(*abr)->fils_gauche);
    afficher_patients(&(*abr)->fils_droit);
}

Consultation* CreerConsult (char* date, char* motif, int nivu) {
    Consultation* new_consult = (Consultation*) malloc(sizeof(Consultation));
    if (new_consult == NULL) return NULL;
    new_consult->date = malloc(sizeof(char) * (strlen(date) + 1));
    if (new_consult->date == NULL) return NULL;
    strcpy(new_consult->date, date);
    new_consult->motif = malloc(sizeof(char) * (strlen(motif) + 1));
    if (new_consult->motif == NULL) return NULL;
    strcpy(new_consult->motif, motif);
    new_consult->niveauUrg = nivu;
    new_consult->suivant = NULL;
    return new_consult;
}

void ajouter_consultation (Parbre* abr, char* nm, char* date, char* motif, int nivu) {
    Patient* patient = rechercher_patient(abr, nm);
    if (patient == NULL) return;
    Consultation* tmp = patient->ListConsult;
    Consultation* tmp_prev = NULL;
    patient->nbrconsult++;
    while (tmp != NULL && strcmp(tmp->date, date) < 0) {
        tmp_prev = tmp;
        tmp = tmp->suivant;
    }
    if (tmp_prev == NULL) { // Ajouter en tête
        tmp_prev = CreerConsult(date, motif, nivu);
        tmp_prev->suivant = tmp;
        patient->ListConsult = tmp_prev;
    } else {
        tmp_prev->suivant = CreerConsult(date, motif, nivu);
        if (tmp == NULL) return; // Ajouter en fin de liste
        tmp_prev->suivant->suivant = tmp; // Ajouter au milieu de la liste
    }
}

Patient* min_abr (Patient* patient) {
    Patient* tmp = patient;
    Patient* tmp_prev = NULL;
    while (tmp->fils_gauche != NULL) {
        tmp_prev = tmp;
        tmp = tmp->fils_gauche;
    }
    if (tmp_prev != NULL) { // Si patient a au moins un fils gauche alors le fils gauche du père du noeud minimal pointe désormais sur NULL
        tmp_prev->fils_gauche = NULL;
    }
    return tmp;
}

void liberer_patient (Patient* patient) {
    Consultation* tmp = patient->ListConsult;
    Consultation* tmp_prev;
    while (tmp != NULL) {
        tmp_prev = tmp;
        tmp = tmp->suivant;
        free(tmp_prev->date);
        free(tmp_prev->motif);
        free(tmp_prev);
    }
    free(patient->nom);
    free(patient->prenom);
    free(patient);
}

void supprimer_patient (Parbre* abr, char *nm) {
    Patient* tmp = (*abr);
    Patient* tmp_prev = NULL;
    Patient* succ;
    int trouve = 0;
    int droite;
    if (*abr == NULL) {
        printf("\nIl n'existe aucun patient dans l'arbre");
        return;
    }
    // Recherche du patient à supprimer (on n'utilise pas la fonction rechercher_patient afin de garder l'information sur le père)
    while (tmp != NULL && trouve == 0) {
        if (strcmp(tmp->nom, nm) > 0) {
            tmp_prev = tmp;
            tmp = tmp->fils_gauche;
        } else if (strcmp(tmp->nom, nm) < 0) {
            tmp_prev = tmp;
            tmp = tmp->fils_droit;
        } else trouve = 1;
    }
    if (trouve == 0) {
        printf("\nLe patient n'exsite pas");
        return;
    }
    if (tmp_prev != NULL) droite = strcmp(tmp_prev->nom, nm) < 0;
    if (tmp->fils_gauche == NULL && tmp->fils_droit == NULL) { // Le noeud à supprimer n'a aucun fils
        if (tmp_prev == NULL) *abr = NULL; // Si on veut supprimer la racine de l'arbre
        else {
            // Trouver si le noeud à supprimer se trouve à droite ou à gauche du père
            if (droite) tmp_prev->fils_droit = NULL;
            else tmp_prev->fils_gauche = NULL;
        }
    } else if (tmp->fils_gauche == NULL) { // Le noeud à supprimer possède un seul fils (droit)
        if (tmp_prev == NULL) *abr = tmp->fils_droit; // Si on veut supprimer la racine de l'arbre
        else {
            if (droite) tmp_prev->fils_droit = tmp->fils_droit;
            else tmp_prev->fils_gauche = tmp->fils_droit;
        }
    } else if (tmp->fils_droit == NULL) { // Le noeud à supprimer possède un seul fils (gauche)
        if (tmp_prev == NULL) *abr = tmp->fils_gauche; // Si on veut supprimer la racine de l'arbre
        else {
            if (droite) tmp_prev->fils_droit = tmp->fils_gauche;
            else tmp_prev->fils_gauche = tmp->fils_gauche;
        }
    } else { // Le noeud à supprimer possède deux fils
        succ = min_abr(tmp->fils_droit); // Successeurs de tmp
        if (tmp_prev == NULL) *abr = succ; // Si on veut supprimer la racine de l'arbre
        else {
            // On remplace le fils correspondant du père du noeud à supprimer par le successeurs de tmp
            if (droite) tmp_prev->fils_droit = succ;
            else tmp_prev->fils_gauche = succ;
        }
        succ->fils_gauche = tmp->fils_gauche;
        // On doit vérifier si le successeur n'est pas le fils droit de tmp (sinon boucle infinie)
        if (succ != tmp->fils_droit) succ->fils_droit = tmp->fils_droit;
    }
    liberer_patient(tmp);
}

void supprimer_arbre (Parbre *abr) {
    if ((*abr) == NULL) return;
    supprimer_arbre(&(*abr)->fils_gauche);
    supprimer_arbre(&(*abr)->fils_droit);
    liberer_patient(*abr);
}

void insertion_maj (Parbre* abr1, Parbre* abr2) {
    if ((*abr1) == NULL) return;
    inserer_patient(abr2,(*abr1)->nom,(*abr1)->prenom);
    insertion_maj((&(*abr1)->fils_gauche), abr2);
    insertion_maj((&(*abr1)->fils_droit), abr2);
}

void maj (Parbre* abr1, Parbre* abr2) {
    while ((*abr2) != NULL) { // Verifier que l'abr2 est bien vide
        supprimer_patient(&(*abr2), (*abr2)->nom);
    }
    insertion_maj(abr1, abr2);
}

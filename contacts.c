/*
 * Gestionnaire de contacts
 * Auteur : Grâce Destinée LEBIKI LAVANYA
 * Description : Gestionnaire de contacts en console
 *               Ajouter, afficher, rechercher, supprimer des contacts
 *               Sauvegarde dans un fichier .txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ══════════════════════════════════════
   CONSTANTES
══════════════════════════════════════ */
#define MAX_CONTACTS  100
#define MAX_NOM       50
#define MAX_TELEPHONE 20
#define MAX_EMAIL     80
#define FICHIER       "contacts.txt"

/* ══════════════════════════════════════
   STRUCTURE Contact
   Un contact = un ensemble de données
   regroupées sous un même nom
══════════════════════════════════════ */
typedef struct {
    char nom[MAX_NOM];
    char prenom[MAX_NOM];
    char telephone[MAX_TELEPHONE];
    char email[MAX_EMAIL];
} Contact;

/* ══════════════════════════════════════
   VARIABLES GLOBALES
   Le tableau de contacts + le compteur
══════════════════════════════════════ */
Contact contacts[MAX_CONTACTS];
int nb_contacts = 0;

/* ══════════════════════════════════════
   PROTOTYPES DES FONCTIONS
   (déclaration avant utilisation)
══════════════════════════════════════ */
void afficher_menu();
void ajouter_contact();
void afficher_contacts();
void rechercher_contact();
void supprimer_contact();
void sauvegarder();
void charger();
void vider_buffer();
void afficher_contact(int index);

/* ══════════════════════════════════════
   FONCTION PRINCIPALE
══════════════════════════════════════ */
int main() {
    int choix;

    /* Chargement des contacts depuis le fichier au démarrage */
    charger();

    printf("\n╔══════════════════════════════════╗\n");
    printf("║   GESTIONNAIRE DE CONTACTS       ║\n");
    printf("║   Grâce Destinée LEBIKI LAVANYA  ║\n");
    printf("╚══════════════════════════════════╝\n");

    /* Boucle principale du programme */
    do {
        afficher_menu();
        printf("Votre choix : ");
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1: ajouter_contact();   break;
            case 2: afficher_contacts(); break;
            case 3: rechercher_contact(); break;
            case 4: supprimer_contact(); break;
            case 5: sauvegarder();
                    printf("✓ Contacts sauvegardés !\n"); break;
            case 0: printf("Au revoir !\n"); break;
            default: printf("⚠ Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}

/* ══════════════════════════════════════
   AFFICHER LE MENU
══════════════════════════════════════ */
void afficher_menu() {
    printf("\n┌─────────────────────────┐\n");
    printf("│  1. Ajouter un contact  │\n");
    printf("│  2. Afficher tous       │\n");
    printf("│  3. Rechercher          │\n");
    printf("│  4. Supprimer           │\n");
    printf("│  5. Sauvegarder         │\n");
    printf("│  0. Quitter             │\n");
    printf("└─────────────────────────┘\n");
}

/* ══════════════════════════════════════
   AJOUTER UN CONTACT
   - Vérifie que le tableau n'est pas plein
   - Demande les infos à l'utilisateur
   - Sauvegarde automatiquement
══════════════════════════════════════ */
void ajouter_contact() {
    /* Vérification : tableau plein ? */
    if (nb_contacts >= MAX_CONTACTS) {
        printf("⚠ Carnet plein ! Maximum %d contacts.\n", MAX_CONTACTS);
        return;
    }

    printf("\n── Nouveau contact ──\n");

    /* Saisie des informations */
    printf("Nom       : ");
    fgets(contacts[nb_contacts].nom, MAX_NOM, stdin);
    /* Supprime le \n à la fin */
    contacts[nb_contacts].nom[strcspn(contacts[nb_contacts].nom, "\n")] = 0;

    printf("Prénom    : ");
    fgets(contacts[nb_contacts].prenom, MAX_NOM, stdin);
    contacts[nb_contacts].prenom[strcspn(contacts[nb_contacts].prenom, "\n")] = 0;

    printf("Téléphone : ");
    fgets(contacts[nb_contacts].telephone, MAX_TELEPHONE, stdin);
    contacts[nb_contacts].telephone[strcspn(contacts[nb_contacts].telephone, "\n")] = 0;

    printf("Email     : ");
    fgets(contacts[nb_contacts].email, MAX_EMAIL, stdin);
    contacts[nb_contacts].email[strcspn(contacts[nb_contacts].email, "\n")] = 0;

    /* Incrémentation du compteur */
    nb_contacts++;

    /* Sauvegarde automatique */
    sauvegarder();

    printf("✓ Contact ajouté ! (%d contact(s) au total)\n", nb_contacts);
}

/* ══════════════════════════════════════
   AFFICHER UN CONTACT (fonction utilitaire)
══════════════════════════════════════ */
void afficher_contact(int index) {
    printf("┌────────────────────────────────┐\n");
    printf("│ #%-2d %-28s│\n", index + 1, "");
    printf("│ Nom       : %-20s │\n", contacts[index].nom);
    printf("│ Prénom    : %-20s │\n", contacts[index].prenom);
    printf("│ Téléphone : %-20s │\n", contacts[index].telephone);
    printf("│ Email     : %-20s │\n", contacts[index].email);
    printf("└────────────────────────────────┘\n");
}

/* ══════════════════════════════════════
   AFFICHER TOUS LES CONTACTS
══════════════════════════════════════ */
void afficher_contacts() {
    if (nb_contacts == 0) {
        printf("Aucun contact enregistré.\n");
        return;
    }

    printf("\n── %d contact(s) ──\n", nb_contacts);
    for (int i = 0; i < nb_contacts; i++) {
        afficher_contact(i);
    }
}

/* ══════════════════════════════════════
   RECHERCHER UN CONTACT
   - Recherche par nom ou prénom
   - strstr() cherche une chaîne dans une autre
══════════════════════════════════════ */
void rechercher_contact() {
    char recherche[MAX_NOM];
    int trouve = 0;

    printf("\nRechercher : ");
    fgets(recherche, MAX_NOM, stdin);
    recherche[strcspn(recherche, "\n")] = 0;

    printf("\n── Résultats pour \"%s\" ──\n", recherche);

    for (int i = 0; i < nb_contacts; i++) {
        /* strstr retourne NULL si pas trouvé, sinon un pointeur */
        if (strstr(contacts[i].nom, recherche) != NULL ||
            strstr(contacts[i].prenom, recherche) != NULL ||
            strstr(contacts[i].email, recherche) != NULL) {
            afficher_contact(i);
            trouve++;
        }
    }

    if (trouve == 0) {
        printf("Aucun contact trouvé pour \"%s\".\n", recherche);
    } else {
        printf("→ %d résultat(s) trouvé(s).\n", trouve);
    }
}

/* ══════════════════════════════════════
   SUPPRIMER UN CONTACT
   - Décale tous les contacts après l'index
   - Décrémente le compteur
══════════════════════════════════════ */
void supprimer_contact() {
    int numero;

    if (nb_contacts == 0) {
        printf("Aucun contact à supprimer.\n");
        return;
    }

    afficher_contacts();
    printf("\nNuméro du contact à supprimer (1-%d) : ", nb_contacts);
    scanf("%d", &numero);
    vider_buffer();

    /* Vérification que le numéro est valide */
    if (numero < 1 || numero > nb_contacts) {
        printf("⚠ Numéro invalide.\n");
        return;
    }

    int index = numero - 1;
    printf("Supprimer %s %s ? (o/n) : ",
           contacts[index].prenom, contacts[index].nom);

    char confirmation;
    scanf("%c", &confirmation);
    vider_buffer();

    if (confirmation == 'o' || confirmation == 'O') {
        /* Décalage des contacts vers la gauche */
        for (int i = index; i < nb_contacts - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        nb_contacts--;
        sauvegarder();
        printf("✓ Contact supprimé.\n");
    } else {
        printf("Suppression annulée.\n");
    }
}

/* ══════════════════════════════════════
   SAUVEGARDER DANS UN FICHIER
   - Ouvre le fichier en écriture ("w")
   - Écrit chaque contact ligne par ligne
   - Ferme le fichier
══════════════════════════════════════ */
void sauvegarder() {
    FILE *fichier = fopen(FICHIER, "w");

    if (fichier == NULL) {
        printf("⚠ Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    for (int i = 0; i < nb_contacts; i++) {
        fprintf(fichier, "%s|%s|%s|%s\n",
                contacts[i].nom,
                contacts[i].prenom,
                contacts[i].telephone,
                contacts[i].email);
    }

    fclose(fichier);
}

/* ══════════════════════════════════════
   CHARGER DEPUIS UN FICHIER
   - Ouvre le fichier en lecture ("r")
   - Lit chaque ligne et découpe avec sscanf
   - Ferme le fichier
══════════════════════════════════════ */
void charger() {
    FILE *fichier = fopen(FICHIER, "r");

    /* Si le fichier n'existe pas encore, c'est normal */
    if (fichier == NULL) return;

    char ligne[256];
    nb_contacts = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL && nb_contacts < MAX_CONTACTS) {
        /* Supprime le \n à la fin */
        ligne[strcspn(ligne, "\n")] = 0;

        /* Découpe la ligne avec le séparateur | */
        char *token = strtok(ligne, "|");
        if (token) strcpy(contacts[nb_contacts].nom, token);

        token = strtok(NULL, "|");
        if (token) strcpy(contacts[nb_contacts].prenom, token);

        token = strtok(NULL, "|");
        if (token) strcpy(contacts[nb_contacts].telephone, token);

        token = strtok(NULL, "|");
        if (token) strcpy(contacts[nb_contacts].email, token);

        nb_contacts++;
    }

    fclose(fichier);
    if (nb_contacts > 0)
        printf("✓ %d contact(s) chargé(s).\n", nb_contacts);
}

/* ══════════════════════════════════════
   VIDER LE BUFFER DU CLAVIER
   - Nécessaire après scanf pour éviter
     les bugs de saisie
══════════════════════════════════════ */
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

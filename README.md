# 📒 Gestionnaire de contacts — C

Gestionnaire de contacts en console développé en C. Permet d'ajouter, afficher, rechercher et supprimer des contacts, avec sauvegarde automatique dans un fichier texte.

## 🎯 Fonctionnalités

- ➕ Ajouter un contact (nom, prénom, téléphone, email)
- 📋 Afficher tous les contacts
- 🔍 Rechercher par nom, prénom ou email
- 🗑️ Supprimer un contact avec confirmation
- 💾 Sauvegarde automatique dans `contacts.txt`
- 📂 Chargement automatique au démarrage

## 🛠️ Compilation et exécution

### Prérequis
- GCC installé (`gcc --version` pour vérifier)
- Sur Windows : installer [MinGW](https://www.mingw-w64.org/)

### Compiler
```bash
gcc src/contacts.c -o contacts
```

### Exécuter
```bash
# Linux / Mac
./contacts

# Windows
contacts.exe
```

## 📚 Concepts C utilisés — explication pédagogique

### 1. Les structures (`struct`)
```c
typedef struct {
    char nom[50];
    char prenom[50];
    char telephone[20];
    char email[80];
} Contact;
```
Une `struct` permet de regrouper plusieurs variables sous un même nom. C'est l'équivalent d'un objet en Python ou JavaScript, mais en C. Ici, un `Contact` regroupe 4 informations.

---

### 2. Les tableaux
```c
Contact contacts[100];
int nb_contacts = 0;
```
On crée un tableau de 100 contacts. `nb_contacts` garde en mémoire combien de cases sont remplies. C'est une gestion manuelle de la mémoire — pas de liste dynamique comme en Python.

---

### 3. Les fichiers (`FILE`)
```c
FILE *fichier = fopen("contacts.txt", "w");
fprintf(fichier, "%s|%s\n", contacts[i].nom, contacts[i].prenom);
fclose(fichier);
```
En C, on ouvre un fichier avec `fopen`, on écrit avec `fprintf`, et on ferme avec `fclose`. Il faut **toujours fermer** le fichier après utilisation.

Modes d'ouverture :
- `"r"` → lecture seule
- `"w"` → écriture (écrase le contenu)
- `"a"` → ajout à la fin

---

### 4. Les pointeurs et `strtok`
```c
char *token = strtok(ligne, "|");
```
`strtok` découpe une chaîne de caractères selon un séparateur. Elle retourne un **pointeur** vers le morceau trouvé. C'est utilisé ici pour lire les contacts depuis le fichier.

---

### 5. `strstr` — recherche dans une chaîne
```c
if (strstr(contacts[i].nom, recherche) != NULL)
```
`strstr` cherche si une chaîne est contenue dans une autre. Elle retourne `NULL` si pas trouvé, sinon un pointeur vers la position. C'est la base de la recherche.

---

### 6. Le buffer clavier
```c
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
```
Après un `scanf`, des caractères restent dans le buffer. Si on ne le vide pas, le prochain `fgets` les lit et ça crée des bugs. Cette fonction vide le buffer caractère par caractère.

---

## 📁 Structure du projet

```
gestionnaire-contacts/
├── src/
│   └── contacts.c    ← code source principal
├── contacts.txt      ← généré automatiquement
└── README.md
```

## 💡 Ce que j'ai appris

- Manipulation de structures en C
- Lecture et écriture de fichiers
- Gestion de tableaux et de chaînes de caractères
- Découpage de chaînes avec `strtok`
- Gestion du buffer clavier avec `scanf`/`fgets`

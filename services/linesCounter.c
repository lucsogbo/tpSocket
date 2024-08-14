#include <stdio.h>
#include <stdlib.h>

// Fonction principale
int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments
    // Le programme attend un seul argument : le nom du fichier à lire
    if (argc != 2) {
        // Si le nombre d'arguments est incorrect, affiche un message d'erreur
        // et l'utilisation correcte du programme, puis retourne 1 pour indiquer une erreur
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // Ouvre le fichier en mode lecture
    FILE *file = fopen(argv[1], "r");
    // Si l'ouverture du fichier échoue, affiche un message d'erreur
    // avec la fonction perror (qui décrit l'erreur) et retourne 1
    if (file == NULL) {
        perror("Error");
        return 1;
    }
    
    // Initialisation des compteurs pour les lignes vides et non vides
    int emptyLines = 0, nonEmptyLines = 0;
    // Un buffer pour stocker chaque ligne lue du fichier
    char buffer[1024];
    
    // Lecture du fichier ligne par ligne avec fgets
    // fgets retourne NULL lorsqu'il atteint la fin du fichier ou en cas d'erreur
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Vérifie si la ligne est vide (si le premier caractère est '\n')
        if (buffer[0] == '\n')
            emptyLines++;  // Incrémente le compteur de lignes vides
        else
            nonEmptyLines++;  // Incrémente le compteur de lignes non vides
    }
    
    // Ferme le fichier après la lecture
    fclose(file);
    
    // Affiche le nombre de lignes vides et non vides
    printf("Empty lines: %d\nNon-empty lines: %d\n", emptyLines, nonEmptyLines);
    
    // Retourne 0 pour indiquer que le programme s'est terminé correctement
    return 0;
}
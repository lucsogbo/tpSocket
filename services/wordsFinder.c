#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Fonction principale du programme
int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments. Le programme nécessite 2 arguments: un nom de fichier et un mot à rechercher
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <word>\n", argv[0]);
        return 1; // Retourne 1 pour indiquer une erreur d'utilisation
    }
    
    // Ouverture du fichier en mode lecture
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error"); // Affiche un message d'erreur si le fichier ne peut pas être ouvert
        return 1; // Retourne 1 pour indiquer une erreur lors de l'ouverture du fichier
    }
    
    // Copie du mot cible (à rechercher) dans une variable locale
    char targetWord[1024];
    strcpy(targetWord, argv[2]);
    
    // Initialisation du compteur de mots trouvés
    int wordCount = 0;
    
    // Buffer pour lire les mots du fichier
    char buffer[1024];
    
    // Boucle de lecture des mots du fichier
    while (fscanf(file, "%s", buffer) == 1) {
        // Si le mot lu est identique au mot cible, incrémente le compteur
        if (strcmp(buffer, targetWord) == 0)
            wordCount++;
    }
    
    // Fermeture du fichier après la lecture
    fclose(file);
    
    // Affiche le nombre d'occurrences du mot cible dans le fichier
    printf("Occurrences of '%s': %d\n", targetWord, wordCount);
    
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments passés au programme
    // Le programme s'attend à recevoir exactement 3 arguments : <filename> <word1> <word2>
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <filename> <word1> <word2>\n", argv[0]);
        return 1;
    }
    
    // Ouverture du fichier en mode lecture
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error"); // Affiche un message d'erreur si le fichier ne peut pas être ouvert
        return 1;
    }

    // Lire le contenu du fichier en mémoire
    // Se positionne à la fin du fichier pour obtenir sa taille
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file); // Taille du fichier
    fseek(file, 0, SEEK_SET); // Retour au début du fichier

    // Allocation de mémoire pour stocker le contenu du fichier
    char *fileContent = malloc(filesize + 1); // +1 pour le caractère nul '\0'
    if (fileContent == NULL) {
        perror("Error"); // Erreur si l'allocation échoue
        fclose(file);
        return 1;
    }
    
    // Lecture du fichier en mémoire
    fread(fileContent, 1, filesize, file);
    fclose(file); // Fermeture du fichier après lecture
    fileContent[filesize] = '\0'; // S'assurer que le contenu est bien terminé par '\0'

    // Remplacement des occurrences de word1 par word2
    char *pos = fileContent;
    size_t len1 = strlen(argv[2]); // Longueur de word1
    size_t len2 = strlen(argv[3]); // Longueur de word2

    // Boucle pour trouver et remplacer chaque occurrence de word1
    while ((pos = strstr(pos, argv[2])) != NULL) {
        size_t lenTail = strlen(pos + len1); // Longueur de la chaîne après word1
        memmove(pos + len2, pos + len1, lenTail + 1); // Décale la partie restante pour faire de la place
        memcpy(pos, argv[3], len2); // Remplace word1 par word2
        pos += len2; // Avance la position après le remplacement
    }

    // Ouverture du fichier en mode écriture pour sauvegarder les changements
    file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("Error");// Affiche une erreur si le fichier ne peut pas être ouvert
        free(fileContent);
        return 1;
    }

    // Écriture du contenu modifié dans le fichier
    fwrite(fileContent, 1, strlen(fileContent), file);
    fclose(file); // Fermeture du fichier après écriture
    free(fileContent); // Libération de la mémoire allouée

    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}
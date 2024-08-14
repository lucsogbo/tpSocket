#include <stdio.h>   // Inclusion de la bibliothèque standard d'entrée/sortie
#include <ctype.h>   // Inclusion de la bibliothèque pour la manipulation des caractères

int main(int argc, char *argv[]) {
    // Vérifie que le programme est appelé avec exactement un argument
    if (argc != 2) {
        // Affiche un message d'erreur si le nombre d'arguments est incorrect
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1; // Retourne 1 pour indiquer une erreur
    }
    
    // Ouvre le fichier en mode lecture et écriture (r+)
    FILE *file = fopen(argv[1], "r+");
    if (file == NULL) {
        // Affiche un message d'erreur si le fichier ne peut pas être ouvert
        perror("Error");
        return 1; // Retourne 1 pour indiquer une erreur
    }
    
    int c;
    // Lit le fichier caractère par caractère jusqu'à la fin du fichier (EOF)
    while ((c = fgetc(file)) != EOF) {
        // Vérifie si le caractère est une lettre minuscule
        if (islower(c))
            c = toupper(c); // Convertit la lettre minuscule en majuscule
        fseek(file, -1, SEEK_CUR); // Recul d'un caractère dans le fichier
        fputc(c, file); // Écrit le caractère modifié (ou non) dans le fichier
    }
    
    fclose(file); // Ferme le fichier pour libérer les ressources
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}
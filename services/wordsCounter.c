#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Fonction principale qui prend en argument le nombre d'arguments (argc) et un tableau d'arguments (argv)
int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments. Il doit être exactement égal à 2, sinon un message d'utilisation est affiché et le programme se termine avec un code d'erreur.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // Ouverture du fichier en mode lecture. Le nom du fichier est passé en argument depuis la ligne de commande.
    FILE *file = fopen(argv[1], "r");
    // Vérification que le fichier a été ouvert correctement. Si ce n'est pas le cas, un message d'erreur est affiché et le programme se termine avec un code d'erreur.
    if (file == NULL) {
        perror("Error");
        return 1;
    }
    
    // Initialisation du compteur de mots
    int wordCount = 0;
    // Déclaration d'un buffer pour stocker chaque mot lu
    char buffer[1024];
    // Boucle pour lire chaque mot du fichier. fscanf retourne 1 si un mot est lu avec succès.
    while (fscanf(file, "%s", buffer) == 1) {
        // Incrémentation du compteur de mots pour chaque mot lu
        wordCount++;
    }
    
    // Fermeture du fichier après la lecture
    fclose(file);
    // Affichage du nombre total de mots trouvés dans le fichier
    printf("Number of words: %d\n", wordCount);
    // Retour du programme avec un code de succès
    return 0;
}
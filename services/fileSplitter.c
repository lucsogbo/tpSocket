#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour découper un fichier en 'n' morceaux de taille égale
void fileSplitter(const char *filename, int n) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(1);
    }

    // Obtenir la taille du fichier
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Calculer la taille de chaque morceau
    long partSize = fileSize / n;
    long lastPartSize = partSize + (fileSize % n); // Pour gérer les restes

    for (int i = 0; i < n; i++) {
        char partFilename[256];
        sprintf(partFilename, "part_%d.txt", i + 1);

        FILE *partFile = fopen(partFilename, "wb");
        if (partFile == NULL) {
            perror("Erreur d'ouverture du fichier de sortie");
            exit(1);
        }

        char *buffer = (char *)malloc(partSize);
        if (i == n - 1) {
            buffer = (char *)realloc(buffer, lastPartSize);
        }
        
        size_t bytesRead = fread(buffer, 1, partSize, file);
        fwrite(buffer, 1, bytesRead, partFile);
        
        free(buffer);
        fclose(partFile);
    }

    fclose(file);
}

// Fonction pour découper un fichier en morceaux de 'size' octets
void fileSplitter2(const char *filename, int size) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(1);
    }

    int partNumber = 1;
    char *buffer = (char *)malloc(size);

    while (!feof(file)) {
        char partFilename[256];
        sprintf(partFilename, "part_%d.txt", partNumber++);

        FILE *partFile = fopen(partFilename, "wb");
        if (partFile == NULL) {
            perror("Erreur d'ouverture du fichier de sortie");
            exit(1);
        }

        size_t bytesRead = fread(buffer, 1, size, file);
        fwrite(buffer, 1, bytesRead, partFile);

        fclose(partFile);
    }

    free(buffer);
    fclose(file);
}

// Fonction principale qui combine les deux précédentes selon les arguments
int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <filename> -n <number_of_parts> | -size <part_size>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    if (strcmp(argv[2], "-n") == 0) {
        int n = atoi(argv[3]);
        fileSplitter(filename, n);
    } else if (strcmp(argv[2], "-size") == 0) {
        int size = atoi(argv[3]);
        fileSplitter2(filename, size);
    } else {
        fprintf(stderr, "Option invalide. Utilisez -n pour le découpage en 'n' morceaux ou -size pour spécifier la taille des morceaux.\n");
        return 1;
    }

    return 0;
}
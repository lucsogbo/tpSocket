#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    // Création du socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Impossible de créer le socket");
    }
    printf("Socket créé\n");

    server.sin_addr.s_addr = inet_addr("192.168.207.196"); // Adresse IP du serveur
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    // Connexion au serveur
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connexion échouée. Erreur");
        return 1;
    }

    printf("Connecté au serveur\n");

    while (1) {
        printf("Entrez une commande (par ex: fileUpper <nom_fichier.txt>): ");
        fgets(message, 1000, stdin);
        message[strcspn(message, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne

        // Envoi du message au serveur
        if (send(sock, message, strlen(message), 0) < 0) {
            printf("Échec de l'envoi\n");
            return 1;
        }

        // Réception de la réponse du serveur
        if (recv(sock, server_reply, 2000, 0) < 0) {
            printf("Réception échouée\n");
            break;
        }

        printf("Réponse du serveur: %s\n", server_reply);
    }

    close(sock);
    return 0;
}

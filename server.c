#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void *handle_client(void *socket_desc);
void execute_service(const char *service, int client_sock);

int main(int argc, char *argv[]) {
    int server_sock, client_sock, c;
    struct sockaddr_in server, client;
    pthread_t thread_id;

    // Création du socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        printf("Impossible de créer le socket");
        return 1;
    }

    // Configuration du serveur
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Liaison du socket
    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Erreur de liaison");
        return 1;
    }

    // Écoute des connexions
    listen(server_sock, 3);

    printf("Serveur en écoute sur le port 8888...\n");
    c = sizeof(struct sockaddr_in);

    while ((client_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&c))) {
        printf("Connexion acceptée\n");

        if (pthread_create(&thread_id, NULL, handle_client, (void *)&client_sock) < 0) {
            perror("Impossible de créer le thread");
            return 1;
        }

        printf("Gestionnaire de client assigné\n");
    }

    if (client_sock < 0) {
        perror("Échec de l'acceptation");
        return 1;
    }

    return 0;
}

void *handle_client(void *socket_desc) {
    int sock = *(int *)socket_desc;
    char client_message[2000];
    int read_size;

    while ((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        client_message[read_size] = '\0';
        printf("Message du client: %s\n", client_message);
        execute_service(client_message, sock);
        memset(client_message, 0, sizeof(client_message));
    }

    if (read_size == 0) {
        printf("Client déconnecté\n");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("Erreur de réception");
    }

    close(sock);
    return 0;
}

void execute_service(const char *service, int client_sock) {
    char command[2048];
    snprintf(command, sizeof(command), "./%s", service);
    
    int result = system(command);

    if (result == -1) {
        char *message = "Erreur lors de l'exécution du service\n";
        send(client_sock, message, strlen(message), 0);
    } else {
        char *message = "Service exécuté avec succès\n";
        send(client_sock, message, strlen(message), 0);
    }
}
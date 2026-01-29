#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define LOG_FILE "conversation_log.txt"

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;


void write_to_log(int client_id, char *message) {
    pthread_mutex_lock(&log_mutex);

    FILE *fp = fopen(LOG_FILE, "a");
    if (fp != NULL) {
        fprintf(fp, "[Client %d]: %s", client_id, message);
        
        size_t len = strlen(message);
        if (len > 0 && message[len - 1] != '\n') {
            fprintf(fp, "\n");
        }
        
        fclose(fp);
    } else {
        perror("Failed to open log file");
    }

    pthread_mutex_unlock(&log_mutex);
}


void echo_handler(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    char *msg = "Connected to Echo Server.\n";
    send(client_socket, msg, strlen(msg), 0);

    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; 

        write_to_log(client_socket, buffer);
        
        write(client_socket, buffer, bytes_read);
    }
}

void *thread_entry(void *arg) {
    int client_socket = *((int *)arg);
    free(arg); 

    pthread_detach(pthread_self());

    echo_handler(client_socket);

    close(client_socket);
    pthread_exit(NULL);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) { perror("Socket failed"); exit(EXIT_FAILURE); }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed"); exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("Listen failed"); exit(EXIT_FAILURE);
    }
    printf("Logging Echo Server listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("New client connected (ID: %d).\n", new_socket);
        
        int *client_sock_ptr = malloc(sizeof(int));
        *client_sock_ptr = new_socket;

        pthread_t tid;
        if (pthread_create(&tid, NULL, thread_entry, (void *)client_sock_ptr) != 0) {
            perror("Thread creation failed");
            free(client_sock_ptr);
            close(new_socket);
        }
    }
    
    return 0;
}
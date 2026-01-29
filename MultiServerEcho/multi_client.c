#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h> 

#define PORT 8080
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1" // Localhost

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE];

    // --- 1. Create Socket ---
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // --- 2. Connect to Server ---
    printf("Connecting to server at %s:%d...\n", SERVER_IP, PORT);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    // Read the welcome message from the server immediately after connecting
    int valread = read(sock, buffer, BUFFER_SIZE);
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("Server: %s\n", buffer);
    }

    // --- 3. Communication Loop ---
    while(1) {
        printf("You: ");
        // Get input from user
        if (fgets(message, BUFFER_SIZE, stdin) == NULL) {
            break; // Exit on EOF (Ctrl+D)
        }

        // Send data to server
        send(sock, message, strlen(message), 0);

        // Check if user wants to quit
        if (strncmp(message, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }

        // Clear buffer and receive response
        memset(buffer, 0, BUFFER_SIZE);
        valread = read(sock, buffer, BUFFER_SIZE);
        
        if (valread > 0) {
            buffer[valread] = '\0';
            printf("Server Echo: %s", buffer);
        } else {
            printf("Server disconnected.\n");
            break;
        }
    }

    // --- 4. Close Connection ---
    close(sock);
    return 0;
}
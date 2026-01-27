#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define PORT 11111    /* the port client will be connecting to */
#define MSG "Hi i am a client\n"
#define MAX_DATA_SIZE 25 /* max number of bytes we can get at once */

int main(int argc, char *argv[]) {
    int sockfd, numbytes;  
    char buf[MAX_DATA_SIZE +1] = {0}; //adding 1 for null terminator
    struct sockaddr_in srv_addr = {0}; //set all fields to 0 (including sin_zero for padding) METHOD1
    
    //create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("socket() failed\n");  //or perror("socket");
        return -1;
    }
    //fill in server internet address structure
    //memset(&srv_addr, 0, sizeof(srv_addr)); //set all fields to 0 (including sin_zero for padding) METHOD2
    srv_addr.sin_family = AF_INET;      /* host byte order */
    //srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    srv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // macro for 0x7F000001 hex equivalent to 127.0.0.1   
    srv_addr.sin_port = htons(PORT);    /* short, network byte order */

    //connect to server, release socket descriptor on failure
    {
    int check = connect(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    if (check== -1) {
        printf("connect() failed\n"); //or perror("connect");
        close(sockfd); //release socket descriptor
        return -2;
    }

    //send data to server, release socket descriptor on failure
    numbytes = send(sockfd, MSG, strlen(MSG), 0);
    if (numbytes == -1) {
        printf("send() failed\n");   //or perror("send");
        close(sockfd);  //release socket descriptor assuming fatal error
        return -3;
    } 
    }
    
    printf("Data sent successfully \n");

   //receive data from server, close socket descriptor if peer disconnects or error occurs
     numbytes = recv(sockfd, buf, MAX_DATA_SIZE, 0); 
    if (numbytes > 0) {
        buf[numbytes] = '\0'; //null terminate the received data
        printf("Received: %s\n", buf);
        
    }    
    if (numbytes == -1) {
        printf("recv() failed\n"); //or perror("recv");
        close(sockfd);
        return -4;
    } else if (numbytes == 0) {
        printf("Server disconnected\n");
        close(sockfd);
        return -5;        
                                                                         
    }
    printf("Press any key to exit...");// Keep the connection open for a while
    getchar();
    printf("Client exiting...\n");
    
}
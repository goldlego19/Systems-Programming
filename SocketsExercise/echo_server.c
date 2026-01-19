#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define PORT 11111
#define BUFFER_SIZE 1024


int main(){
    int listenfd, connfd;
    struct sockaddr_in srv_addr = {0};
    char buf[BUFFER_SIZE];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1){
        printf("socket() failed\n");
        return -1;
    }

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr =htonl(INADDR_LOOPBACK);
    srv_addr.sin_port = htons(PORT);

    int check = bind(listenfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    if (check!=0){
        printf("bind() failed\n");
        close(listenfd);
        return -2;
    }

    check = listen(listenfd,5);
    if(check!= 0) {
        printf("listen() failed\n");
        close(listenfd);
        return -3;
    }
    printf("Server listening on port %d...\n", PORT);

    connfd = accept(listenfd,NULL,NULL);
    if (connfd == -1){
        printf("accept() failed\n");
    }else{
        printf("Client connected successfully\n");
        while(1){
            memset(buf,0,BUFFER_SIZE);
            ssize_t bytes = recv(connfd,buf,BUFFER_SIZE-1,0);

            

            printf("Client:%s",buf);
            char upperBuffer[BUFFER_SIZE];

            for(int i = 0;buf[i]!= '\0';i++){
                upperBuffer[i] = toupper((unsigned char)buf[i]);
            }
            upperBuffer[strlen(buf)] = '\0';
            send(connfd, upperBuffer, strlen(buf),0);
        }
        close(connfd);
        close(listenfd);
    }

}
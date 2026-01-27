#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define PORT 11111

int main() {
    int listenfd, connfd;
    struct sockaddr_in srv_addr = {0}; //set all fields to 0 (including sin_zero for padding) METHOD1
    char buf[128];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        printf("socket() failed\n");
        return -1;
    }
    //memset(&src_adr, 0, sizeof(srv_addr)); //set all fields to 0 (including sin_zero for padding) METHOD2
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    srv_addr.sin_port = htons(PORT);

    int check = bind(listenfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    if (check != 0) {
        printf("bind() failed\n");
        close(listenfd);
        return -2;
    }
    check = listen(listenfd, 5);
    if(check!= 0) {
        printf("listen() failed\n");
        close(listenfd);
        return -3;
    }
    printf("Server listening on port %d...\n", PORT);

    connfd = accept(listenfd, NULL, NULL); //ignore client address
    if (connfd == -1) {
        printf("accept() failed\n");
        //on real servers we do not disconnect but aretry 
        
    } else { 
        printf("Client connected successfully\n");
        int n;
        n = recv(connfd, buf, sizeof(buf)-1, 0);
        if(n>0) {
            buf[n] = '\0';
            printf("Server received: %s", buf);
 
            int bytes = send(connfd, "Hello from server\n", 18, 0);
            if (bytes == -1) {
                printf("send() failed\n");
        }

       
        //sleep(60); // Keep the connection open for a while
        printf("Press any key to exit...");// Keep the connection open for a while
        getchar();
        close (connfd);    
    }
        
  
    printf("Server exiting...\n");
    close(listenfd);
    return 0;
  }
}
#include "tcp.h"
#include "head.h"

int create_tcp_socket(int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }
    printf("TCP Socket Create Success\n");
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind");
        exit(1);
    }
    
    printf("TCP Socket Bind Success\n");

    if (listen(sockfd, 25) < 0) {
        perror("listen");
        exit(1);
    }

    printf("TCP Listen Success\n");
    return sockfd;
}

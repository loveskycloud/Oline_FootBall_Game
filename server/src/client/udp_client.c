#include "head.h"

int create_udp_socket_client() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    printf("UDP Create Socket Success\n");
    return sockfd;
}

int client_udp_connect(int sockfd) {
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr((char *)server_ip);
    
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        exit(1);
    }

    printf("udp connect success!\n");
    return 1;
}

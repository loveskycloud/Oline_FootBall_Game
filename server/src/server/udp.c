#include "head.h"

extern int server_port;
extern int clientport;
extern char server_ip[20];
/*
int udp_connect(char *ip_addr, int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    printf("Create Socket Success!\n");
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip_addr);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        return -1;
    }
    printf("Connect Success!\n");
    return sockfd;
}

int udp_socket(int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    printf("Create Udp Socket!\n");
    return sockfd;
}

*/
int create_server_udp_socket(int clientport = 8888) {
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    printf("UDP Create Socket Success\n");
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(clientport);
    server.sin_addr.s_addr = INADDR_ANY;
    
    int opt = 1;

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
  //  make_nonblock(sockfd);

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind");
        exit(1);
    }

    printf("UDP Bind Socket Success\n");
    return sockfd;
}



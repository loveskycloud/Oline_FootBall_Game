#include "head.h"

void add_event(int epollfd, int fd, int event) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void del_event(int epollfd, int fd, int events) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}
 
int udp_connect(int epollfdd, struct sockaddr *serveraddr) {
    int sockfd;
    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) < 0) {
        perror("connect");
        return -1;
    }
}

int udp_accept(int epollfd, int fd) {
    struct sockaddr_in client;
    int new_fd, ret;
    char msg[512] = {0};
    socklen_t len = sizeof(struct sockaddr_in);
    ret = recvfrom(fd, msg, sizeof(msg), 0, (struct sockaddr *)&client, &len);
    if (ret < 0) {
        return -1;
    }
    
    DBG(GREEN "INFO" NONE " : %s : %d login!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    new_fd = udp_connect(epollfd, (struct sockaddr *)&client);
    return new_fd;
}

#include "head.h"

void add_event(int epollfd, int fd, int events) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void add_event_ptr(int epollfd, int fd, int events, struct User *user) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = (void *)user;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    DBG(GREEN "Sub Thread" NONE " : After Epoll Add %s.\n", user->name);
}

void del_event(int epollfd, int fd, int events) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}
 
int udp_connect(int epollfd, struct sockaddr *serveraddr) {
    int sockfd;
    if ((sockfd = create_udp_socket()) < 0) {
        perror("socket_udp");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) < 0) {
        perror("connect");
        return -1;
    }
    return sockfd;
}

int udp_accept(int epollfd, int fd) {
    struct sockaddr_in client;
    int new_fd, ret;
    struct LogRequest request;
    struct LogResponse response;
    
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));

    socklen_t len = sizeof(struct sockaddr_in);
    ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len);

    if (ret != sizeof(request)) {
        response.type = 1;
        strcpy(response.msg, "Login failed.");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;
    }

    response.type = 0;
    strcpy(response.msg, "Login success. Enjoy yourself.");
    sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
    
    if (request.team) {
        DBG(GREEN "INFO" NONE " : " BLUE " %s on %s:%d login! (%s)\n" NONE, request.name, inet_ntoa(client.sin_addr), ntohs(client.sin_port), request.msg);
    } else {
        DBG(GREEN "INFO" NONE " : " RED " %s on %s:%d login! (%s)\n" NONE, request.name, inet_ntoa(client.sin_addr), ntohs(client.sin_port), request.msg);
    } 


    strcpy(user->name, request.name);
    user->team = request.team;
    DBG(GREEN "INFO" NONE " : %s : %d login!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    user->fd = new_fd;
    new_fd = udp_connect(epollfd, (struct sockaddr *)&client);

    return new_fd;
}

int find_sub(struct User *team) {
    for (int i = 0; i < MAX; i++) {
        if (!team[i].online) return i;
    }
    return -1;
}

void add_to_sub_reactor(struct User *user) {
    struct User *team = (user->team ? bteam : bteam);
    DBG(YELLOW "Main Thread : " NONE "Add to sub_reactor\n");
    int sub = find_sub(team);
    team[sub] = *user;
    team[sub].online = 1;
    team[sub].flag = 10;
    DBG(L_RED "sub = %d, name = %s\n" NONE, sub, team[sub].name);
    if (user->team) {
        add_event_ptr(bepollfd, team[sub].fd, EPOLLIN | EPOLLET, &team[sub]);
    } else {
        add_event_ptr(repollfd, team[sub].fd, EPOLLIN | EPOLLET, &team[sub]);
    }
}

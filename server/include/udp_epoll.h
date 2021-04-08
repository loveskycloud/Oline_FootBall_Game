#pragma once
#include "head.h"

extern int port;
extern struct User *rteam;
extern struct User *bteam;
extern int repollfd, bepollfd;

void add_event(int epollfd, int fd, int events);
void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epollfd, int fd, int events);
int udp_connect(int epollfd, struct sockaddr *serveraddr);
int udp_accept(int epollfd, int fd);
int find_sub(struct User *team);
void add_to_sub_reactor(struct User *user);

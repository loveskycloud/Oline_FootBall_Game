#pragma once

extern char server_ip[20];
extern int server_port;

int create_udp_socket_client();
int client_udp_connect(int sockfd);

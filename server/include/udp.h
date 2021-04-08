#pragma once

int create_udp_socket();
int create_udp_socket_client();
int client_udp_connect(int sockfd);
int udp_socket(int port);
int udp_connect(char *ip_addr, int port);

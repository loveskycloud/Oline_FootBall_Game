#include "head.h"


char conf[] = "./other/conf";


int main(int argc, char **argv)
{

    int sockfd;
    int opt;
    while ((opt = getopt(argc, argv, "h:p:")) != -1) {
        switch(opt) {
        case 'h':
            strcpy(server_ip, optarg);
            break;
        case 'p':
            server_port = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage : %s [-h host] [-p port]!\n", argv[0]);
            exit(1);
        }
    }

    argc -= (optind - 1);
    argv += (optind - 1);

    if (argc > 1) {
        fprintf(stderr, "Usage : %s [-h host] [-p port]!\n", argv[0]);
        exit(1);
    }

    if (!server_port) server_port = atoi(get_value(conf, "PORT"));
    if (!strlen(server_ip)) strcpy(server_ip, get_value(conf, "SERVERIP"));

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip);

    socklen_t len = sizeof(server);

    printf(GREEN "INFO" NONE " : server_ip = %s, server_port = %d\n", server_ip, server_port);

    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        exit(1);
    }

    sendto(sockfd, "HI", sizeof("HI"), 0, (struct sockaddr *)&server, len);

    sleep(10);
    return 0;
}


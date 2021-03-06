#include "head.h"
#include "game.h"

char conf[] = "./other/client.conf";
char server_ip[20] = {0};
int server_port = 0;
int sockfd;

int main(int argc, char **argv)
{
    int opt;
    pthread_t recv_t;
    struct LogRequest request;
    struct LogResponse response;
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));

    while ((opt = getopt(argc, argv, "h:p:n:t:m:")) != -1) {
        switch(opt) {
        case 'h':
            strcpy(server_ip, optarg);
            break;
        case 'p':
            server_port = atoi(optarg);
            break;
        case 'n':
            strcpy(request.name, optarg);
            break;
        case 't':
            request.team = atoi(optarg);
            break;
        case 'm':
            strcpy(request.msg, optarg);
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

    if (!server_port) server_port = atoi(get_value(conf, (char *)"PORT"));
    if (!strlen(server_ip)) strcpy(server_ip, get_value(conf, (char *)"SERVERIP"));
    if (!strlen(request.name)) strcpy(request.name, get_value(conf, (char *)"NAME"));
    if (!strlen(request.msg)) strcpy(request.msg, get_value(conf, (char *)"LOGMSG"));
    if (!request.team) request.team = atoi(get_value(conf, "TEAM"));

    if ((sockfd = create_udp_socket_client()) < 0) {
        perror("create_udp_socket_client");
        return -1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip);

    socklen_t len = sizeof(server);

    printf(GREEN "INFO" NONE " : server_ip = %s, server_port = %d, name = %s, team = %s logmsg = %s\n", server_ip, server_port, request.name, (request.team == 0 ? "BLUE" : "RED"), request.msg);


    sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&server, len);

    fd_set set;
    FD_ZERO(&set);
    FD_SET(sockfd, &set);
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    int retval = select(sockfd + 1, &set, NULL, NULL, &tv);

    if (retval == -1) {
        perror("select");
        exit(1);
    } else if (retval) {
        int ret = recvfrom(sockfd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&server, &len);

        if (ret != sizeof(response) || response.type) {
            DBG(RED "ERROR : " NONE "The Game Server refused your login.\n\t This May be helpfull: %s\n", response.msg);
            exit(1);
        }
    } else {
        DBG(RED "ERROR : " NONE "The Game Server is out of service.\n");
        exit(1);
    }

    connect(sockfd, (struct sockaddr *)&server, len);

    pthread_create(&recv_t, NULL, client_recv, NULL);

        while (1) {
            struct FootBallMsg msg;
            msg.type = FT_MSG;
            DBG(YELLOW "Input Message : " NONE);
            fflush(stdout);
            scanf("%[^\n]s", msg.msg);
            getchar();
            send(sockfd, (void *)&msg, sizeof(msg), 0);
        }
    return 0;
}


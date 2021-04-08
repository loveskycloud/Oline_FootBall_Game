#include "head.h"

struct Map court;

char conf[] = "./other/server.conf";
//client temp add
char server_ip[] = "127.0.0.1";
struct User *rteam;
struct User *bteam;
extern WINDOW *Football, *Message, *Help, *Score, *Write;
int port;
int server_port = 8888;
int epoll_fd;
int repollfd;
int bepollfd;


int main(int argc, char **argv) {
    int opt;
    int data_port;
    int listener;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch((char)opt) {
        case 'p':
            port = atoi(argv[2]);
            break;
        default:
            fprintf(stderr, "Usage: %s [-p port]\n", argv[1]);
            exit(1);
        }
    }
    argc -= (optind - 1);
    argv += (optind - 1);

    if (argc > 1) {
        fprintf(stderr, "Usage: %s [-p port]\n", argv[1]);
        exit(1);
    }

    if (!port) port = atoi(get_value(conf, (char *)"PORT"));

    court.width = atoi(get_value(conf, (char *)"COLS"));
    court.height = atoi(get_value(conf, (char *)"LINES"));
    data_port =  atoi(get_value(conf, (char *)"DATAPORT"));
    court.start.x = 1;
    court.start.y = 1;

    rteam = (struct User *)calloc(MAX, sizeof(struct User));
    bteam = (struct User *)calloc(MAX, sizeof(struct User));

    if ((listener = create_udp_socket()) < 0) {
        perror("create_udp_socket");
        exit(1);
    }

    DBG(GREEN "INFO" NONE " : Server start on port %d\n", port);

    pthread_t tid;

    pthread_t red_t;
    pthread_t blue_t;
    /* pthread_t heart_t; */

        /* pthread_create(&tid, NULL, draw, NULL); */
    
    epoll_fd = epoll_create(MAX * 2);
    repollfd = epoll_create(MAX);
    bepollfd = epoll_create(MAX);

    if (epoll_fd < 0 || repollfd < 0 || bepollfd < 0) {
        perror("epoll_create");
        exit(1);
    }
    
    

    struct task_queue redQueue;
    struct task_queue blueQueue;

    task_queue_init(&redQueue, MAX, repollfd);
    task_queue_init(&blueQueue, MAX, bepollfd);
    
    pthread_create(&red_t, NULL, sub_reactor, (void *)&redQueue);
    pthread_create(&blue_t, NULL, sub_reactor, (void *)&blueQueue);
    /* pthread_create(&heart_t, NULL, heart_beat, NULL); */


    struct epoll_event ev, events[MAX * 2];
    ev.events = EPOLLIN;
    ev.data.fd = listener;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listener, &ev);

    struct sockaddr_in client;  
    socklen_t len = sizeof(client);

    while (1) {
        //TODO
        /* w_gotoxy_puts(Message, 1, 1, (char *)"等待连接"); */
        /* wrefresh(Message); */
        //FIXME
        
        
        DBG(YELLOW "Main Thread" NONE " : before epollfd_wait\n");
        int nfds = epoll_wait(epoll_fd, events, MAX * 2, -1); //-1 block 0 nblock
        DBG(YELLOW "Main Thread" NONE " : After epollfd_wait\n");

        for (int i = 0; i < nfds; i++) {
            struct User user;
            char buff[512] = {0};
            DBG(YELLOW "EPOLL" NONE " : Doing with %dth fd\n", i);
            if (events[i].data.fd ==listener) {

                int new_fd = udp_accept(epoll_fd, listener, &user);
                if (new_fd > 0) {
                    DBG(YELLOW "Main Thread" NONE " : Add %s to %s sub_reactor.\n", user.name, (user.team ? "BLUE" : "RED"));
                    add_to_sub_reactor(&user);
                }
            } else {
                recv(events[i].data.fd, buff, sizeof(buff), 0);
                printf(PINK "RECV" NONE " : %s\n", buff);
            }
        }
            /* char info[512] = {0}; */
            /* recvfrom(events[i].data.fd, (void *)&info, sizeof(info), 0 ,(struct sockaddr *)&client, &len); */

            /* sprintf(info, "Login: %s : %d", inet_ntoa(client.sin_addr), ntohs(client.sin_port)); */
            /* w_gotoxy_puts(Message, 2, 1, info); */

        /* char msg[512] = {0}; */
        /* recvfrom(listener, (void *)&lg, sizeof(lg), 0, (struct sockaddr *)&client, &len); */
        /* sprintf(msg, "Login: %s : %d", inet_ntoa(client.sin_addr), ntohs(client.sin_port)); */
        /* int inc = 0; */
        /* w_gotoxy_puts(Message, ++inc, 1, msg); */
    }

    return 0;
}


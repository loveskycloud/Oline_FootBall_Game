#include "head.h"
#include "color.h"
#include "game.h"
#include "draw.h"
#include "udp.h"
struct Map court;

char conf[] = "./other/server.conf";

int main(int argc, char **argv) {
    int port =  0, opt;
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
    court.start.x = 1;
    court.start.y = 1;

    if ((listener = create_udp_socket(port)) < 0) {
        perror("create_udp_socket");
        exit(1);
    }

    DBG(GREEN "INFO" NONE " : Server start on port %d\n", port);

    pthread_t tid;

    pthread_create(&tid, NULL, draw, NULL);
    while (1) {
        //todo
    }
    
    return 0;
}


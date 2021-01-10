#include "head.h"
#include "color.h"
int main(int argc, char **argv) {
    int port, opt;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch(opt) {
            case 'p':
                port = atoi(argv[1]);
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
    
    //if (!port) port = atoi(get_value(conf, "PORT"));

    DBG(GREEN "INFO" NONE " : Server start on port %d\n", port);

    return 0;
}


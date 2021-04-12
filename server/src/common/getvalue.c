#include "head.h"

char *get_value(char *path, char *pattern) {
    FILE *file;
    if ((file = fopen(path, "r")) == nullptr) {
        fprintf(stderr, "the %s file is not exist", path); 
        exit(1);
    }
    
    char *line = NULL; 
    size_t len;
    char *findstr;
    char *ans = (char *)malloc(sizeof(50));
    while (getline(&line, &len, file) != -1) {
        if (((findstr = strstr(line, pattern)) != NULL) && (line[strlen(pattern)] == '=')) {
            strcpy(ans, line + strlen(pattern) + 1);
            break;
        } 
    }
    free(line);
    ans[strlen(ans) - 1] = '\0';
    return ans;
}

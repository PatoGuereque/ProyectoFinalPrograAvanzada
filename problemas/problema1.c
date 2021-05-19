#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"

void problema1(const int connfd, const int n) {
    char *buffer = malloc(sizeof(char *) * 1000);
    write_curr_time(buffer);
    printf("Time: %s\n", buffer);
    free(buffer);
}
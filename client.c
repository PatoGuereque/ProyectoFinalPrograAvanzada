#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include "client.h"

void handle_client(client_t *self) {
    // do stuff
    char *buffer = (char *)malloc(10000*sizeof(char));
    read(self->connfd, buffer, 10000);
    int num = atoi(buffer);
    printf("[Client %d] Recieved: %d\n", self->internal_id, num);

    sprintf(buffer, "OK! %d", num);    
    write(self->connfd, buffer, strlen(buffer));

    self->close_client((void *)self);
}
#ifndef CLIENT_H
#define CLIENT_H
#include <sys/types.h>

typedef struct client_t {

    pthread_t thread_id;
    int internal_id;
    int connfd;
    void (*close_client)(void*);

} client_t;

void handle_client(client_t *self);

#endif
#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h> 
#include <stdlib.h>
#include <netinet/in.h>
#include "constants.h"
#include "problemas.h"
#include "client.h"

// threads
pthread_mutex_t lock;
pthread_cond_t cv;
int max_threads = 0;
int threads_available = 0;
client_t** clients;

// server socket
int serverfd;

void *client_thread(void *arg) {
    client_t *client = (client_t *) arg;
    handle_client(client);
    return 0;
}

void close_client(void* args) {
    client_t *client = (client_t *) args;
    close(client->connfd);
    pthread_mutex_lock(&lock);
    threads_available++;
    int intid = client->internal_id;
    free(client);
    *(clients+intid) = NULL;
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&lock);
    printf("[Client %d] disconnected.\n", intid);
}

void close_connections() {
   printf("Closing all connections!\n");
   close(serverfd);

   for (int i = 0; i < max_threads; i++) {
       if (*(clients+i) != NULL) {
           close_client(*(clients+i));
       }
   }

   free(clients);
   exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <num_threads>\n", argv[0]);
        return -1;
    }

    signal(SIGINT, close_connections);

    // read number of threads
    max_threads = atoi(argv[1]);
    clients = malloc(sizeof(client_t *) * max_threads);
    threads_available = max_threads;

    // create the socket
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Unable to bind\n");
        close(serverfd);
        exit(1);
    }

    if (listen(serverfd, 1) == -1) {
        perror("Unable to listen\n");
        exit(1);
    }

    printf("[Server] Started listening for new connections on port :%d\n", PORT);
    while (1) {
        if (threads_available == 0) {
            pthread_mutex_lock(&lock);
            pthread_cond_wait(&cv, &lock);
            pthread_mutex_unlock(&lock);
        }

        client_t *client = malloc(sizeof(client_t));
        client->connfd = accept(serverfd, (struct sockaddr *)NULL, NULL);
        client->close_client = &close_client;

        if (pthread_create(&client->thread_id, NULL, client_thread, (void *)client) < 0) {
            perror("pthread_create");
            exit(1);
        } else {
            pthread_mutex_lock(&lock);
            for (int i = 0; i < max_threads; i++) {
                if (*(clients+i) == NULL) {
                    client->internal_id = i;
                    *(clients+i) = client;
                    break;
                }
            }
            threads_available--;
            printf("[Client %d] connected\n", client->internal_id);
            pthread_mutex_unlock(&lock);
        }
    }
    return 0;
}

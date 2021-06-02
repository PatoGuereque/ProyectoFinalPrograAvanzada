#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <string.h>
#include "constants.h"

#define IP "127.0.0.1"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <número>\n", argv[0]);
        return -1;
    }

    if (!atoi(argv[1])) {
        perror("invalid args");
        exit(-1);
    }

    int connfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &addr.sin_addr);

    if (connect(connfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Unable to connect\n");
        close(connfd);
        exit(1);
    }

    // send the number param
    write(connfd, argv[1], strlen(argv[1]));

    char *buffer = (char *)malloc(10000*sizeof(char));
    read(connfd, buffer, 10000);
    printf("Recieved: %s\n", buffer);
    free(buffer);

    close(connfd);
    return 0;
}

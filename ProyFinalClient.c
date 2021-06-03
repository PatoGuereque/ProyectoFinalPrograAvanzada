#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "utils.h"

#define IP "127.0.0.1"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <número>\n", argv[0]);
        return -1;
    }

    int num = atoi(argv[1]);
    if (!is_number(argv[1])) {
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
    write(connfd, &num, sizeof(num));

    int messages;
    read(connfd, &messages, sizeof(int));
    while (messages--) {
        size_t response_bytes;
        read(connfd, &response_bytes, sizeof(size_t));

        char *buffer = malloc(response_bytes * sizeof(char));
        read(connfd, buffer, response_bytes);
        printf("%s\n", buffer);
        free(buffer);
    }

    close(connfd);
    return 0;
}

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "client.h"

#define TIME_SIZE 8

void write_curr_time(char *tstring) {
    /* get seconds since the Epoch */
    time_t secs = time(0);

    /* convert to localtime */
    struct tm *local = localtime(&secs);

    /* and set the string */
    sprintf(tstring, "%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
}

void write_number_messages(client_t *client, int num) {
    write(client->connfd, &num, sizeof(num));
}

void write_response(client_t *client, char *message) {
    char *time_string = malloc(TIME_SIZE + 1);  // +1 for '\0'
    write_curr_time(time_string);

    size_t response_size = snprintf(NULL, 0, "[%s]: %s", time_string, message) + 1;  // +1 for '\0'
    char *response = malloc(response_size);
    sprintf(response, "[%s]: %s", time_string, message);

    write(client->connfd, &response_size, sizeof(size_t));
    write(client->connfd, response, response_size);

    free(time_string);
    free(response);
}

void write_raw_response(client_t *client, char *message) {
    size_t message_size = strlen(message);
    write(client->connfd, &message_size, sizeof(size_t));
    write(client->connfd, message, message_size);
}

int is_number(char *text) {
    int j;
    j = strlen(text);
    while (j--) {
        if (text[j] >= '0' && text[j] <= '9') {
            continue;
        }

        return 0;
    }
    return 1;
}
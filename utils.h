#ifndef UTILS_H
#define UTILS_H
#include "client.h"
#define TIME_SIZE 8

void write_curr_time(char *string);
void write_number_messages(client_t *client, int num);
void write_raw_response(client_t *client, char *message);
void write_response(client_t *client, char *message);
int is_number(char *text);

#endif

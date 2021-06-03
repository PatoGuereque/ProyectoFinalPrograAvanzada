#include <stdio.h>
#include <stdlib.h>
#include "../client.h"
#include "../utils.h"

void problema4(client_t *client, const int n) {
    write_number_messages(client, 2);
    write_response(client, "Solving for problem 4");

    char *time_string = malloc(TIME_SIZE + 1);  // +1 for '\0'
    write_curr_time(time_string);

    char *head = "<!DOCTYPE html>"
    "<html>"
        "<head>"
            "<meta content=\"text/html; charset=utf-8\" http-equiv=\"Content-Type\">"
            "<title>Proyecto final</title>"
        "</head>"
        "<body>"
            "<p>Current Time:";
    char *rest = ""
            "</p>"
        "</body>"
    "</html>";
    size_t response_size = snprintf(NULL, 0, "%s%s%s", head, time_string, rest) + 1;  // +1 for '\0'
    char *response = malloc(response_size);
    sprintf(response, "%s%s%s", head, time_string, rest);
    write_raw_response(client, response);

    free(time_string);
    free(response);
}
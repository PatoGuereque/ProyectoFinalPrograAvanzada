#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include "utils.h"
#include "client.h"
#include "problemas.h"

void handle_client(client_t *self) {
    // do stuff
    int num;
    read(self->connfd, &num, sizeof(num));
    printf("[Client %d] Recieved: %d\n", self->internal_id, num);
    if (num % 9 == 0) {
        problema1(self, num);
    } else if (num % 7 == 0) {
        problema2(self, num);
    } else if (num % 5 == 0) {
        problema3(self, num);
    } else if (num % 3 == 0) {
        problema4(self, num);
    } else if (num % 2 == 0) {
        problema5(self, num);
    } else {
        write_number_messages(self, 1);
        write_response(self, "Number didn't match any criteria.");
    }

    // close the socket connection
    self->close_client((void *)self);
}
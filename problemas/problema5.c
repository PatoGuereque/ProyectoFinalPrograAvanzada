#include "../client.h"
#include "../utils.h"

void problema5(client_t *client, const int n) {
    write_number_messages(client, 2);
    write_response(client, "Solving for problem 5");

    write_response(client, "Answer is 42!");
}
#include "../utils.h"
#include "../client.h"

void problema1(client_t *client, const int n) {
  write_number_messages(client, 2);
  write_response(client, "Solving for problem 1");

  write_response(client, "Answer is 42!");
}
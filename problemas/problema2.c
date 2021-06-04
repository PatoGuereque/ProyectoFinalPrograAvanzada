#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <omp.h>
#include <pthread.h>
#include <math.h>

#include "../client.h"
#include "../utils.h"

void problema2(client_t *client, const int n) {
    write_number_messages(client, 2);
    write_response(client, "Solving for problem 2");
    double pi = 0;
    char response[50];
    omp_set_num_threads(6);
    #pragma omp parallel reduction (+:pi)
    {
        pi += asin(0.5);
    }
    sprintf(response, "Value of pi is: %.10f", pi);
    write_response(client, response);
}
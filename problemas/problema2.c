#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../client.h"
#include "../utils.h"

struct args_t {
    pthread_t thread_id;
    long pointsToIterate;
    unsigned int seed;
};

void *calculate(void *arg) {
    struct args_t *args = arg;
    long *points;

    if ((points = (long *)malloc(sizeof(long *))) == NULL) {
        perror("malloc() error");
        exit(2);
    }
    *points = 0;

    double x, y;
    for (long i = 0; i < args->pointsToIterate; i++) {
        /* 
         * "The function rand() is not reentrant or thread-safe"
         * For this reason we will use rand_r, as this will be
         * thread safe. 
         * 
         * https://linux.die.net/man/3/rand
         */
        x = rand_r(&(args->seed)) / ((double)(unsigned)RAND_MAX + 1);
        y = rand_r(&(args->seed)) / ((double)(unsigned)RAND_MAX + 1);

        if (x * x + y * y < 1) {
            *points += 1;
        }
    }

    pthread_exit(points);
}

void problema2(client_t *client, const int n) {
    write_number_messages(client, 2);
    write_response(client, "Solving for problem 2");
    time_t start = time(NULL);
    srand(start);

    unsigned long points = 1000000000;  // 1,000,000,000
    double pi;
    int numThreads = 8;  // lets use 8 threads to calculate pi
    unsigned long pointsToIterate = points / numThreads;
    unsigned long totalPoints = pointsToIterate * numThreads;  // fix for floor division
    unsigned long pointsInside = 0;
    unsigned int seed = rand();
    struct args_t threadInfo[numThreads];

    for (int i = 0; i < numThreads; i++) {
        threadInfo[i].pointsToIterate = pointsToIterate;
        threadInfo[i].seed = seed++;

        if (pthread_create(&threadInfo[i].thread_id, NULL, &calculate, &threadInfo[i]) != 0) {
            perror("pthread_create fail");
            exit(1);
        }
    }

    for (int i = 0; i < numThreads; i++) {
        long *points;
        pthread_join(threadInfo[i].thread_id, (void *)&points);
        pointsInside += *points;
    }

    pi = (4.0 * (double)pointsInside) / ((double)totalPoints);

    size_t num_bytes = snprintf(NULL, 0, "Value of pi is: %.10lf", pi) + 1; // +1 for '\0'
    char *response = malloc(num_bytes);
    sprintf(response, "Value of pi is: %.10lf", pi);
    write_response(client, response);
    free(response);
}
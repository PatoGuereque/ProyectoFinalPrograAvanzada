#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <omp.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include "../client.h"
#include "../utils.h"

int MIN_PARTS = 5;
int sum = 0;

void problema3(client_t *client, const int n) {
    write_number_messages(client, 2);
    write_response(client, "Solving for problem 3");

    srand(time(0));
    char response[50];
    int num = 5;
    int mat[num][num];
    int x;

    for(int i=0; i<num; i++){
        for(int j=0; j<num; j++){
            mat[i][j] = rand() % 10;
        }
    }

    omp_set_num_threads(5);
    #pragma omp parallel
    {
        x = omp_get_thread_num();
        for(int i=(x*(num/5)); i<((x+1)*(num/5)); i++){
            for(int j=0; j<num; j++){
                sum += mat[i][j];
            }
        }
    }

    sprintf(response, "La sumatoria total es: %d", sum);
    write_response(client, response);
}
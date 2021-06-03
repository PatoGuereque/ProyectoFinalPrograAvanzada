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

int primos(int num){
    if(num != -1 && num > 0){
        int primo = 0;
        int aux = 2;
        while(aux<num && primo != 1){
            if(num % aux == 0) primo = 1;
            aux++;
        }
        if(primo == 0){
            return num;
        }
    }
    return -1;
}

int primos2(int num){
    if (num & 1){
        num -= 2;
    } else {
        num--;
    }

    int i, j;
    for (i = num; i >= 2; i -= 2) {
        if (i % 2 == 0){
            continue;
        }
        for (j = 3; j <= sqrt(i); j += 2) {
            if (i % j == 0){
                break;
            }
        }
        if (j > sqrt(i)){
            return i;
            break;
        }
    }
 
    return 2;
}

void problema5(client_t *client, const int n) {
    char closest_num[10];
    char response[50];
    write_number_messages(client, 2);
    write_response(client, "Solving for problem 5");
    int num_menor = primos2(n);
    int num_mayor = -1;
    int num_aux = num_menor+1;
    while(num_mayor == -1){
        num_mayor = primos(num_aux);
        num_aux++;
    }
    if(abs(num_menor-n) >= abs(num_mayor-n)){
        sprintf(response, "El número primo más cercano es: %d", num_mayor);
    } else {
        sprintf(response, "El número primo más cercano es: %d", num_menor);
    }
    write_response(client, response);
}
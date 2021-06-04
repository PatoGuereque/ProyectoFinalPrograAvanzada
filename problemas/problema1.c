#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../client.h"
#include "../utils.h"

void problema1(client_t *client, const int n) {
    write_number_messages(client, 2);
    write_response(client, "Solving for problem 1");
    srand(time(NULL));

    int arr[n];
    double xSum = 0, x2Sum = 0, ySum = 0, y2Sum = 0, xy = 0;
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;

        xSum += i;
        x2Sum += i * i;
        ySum += arr[i];
        y2Sum += arr[i] * arr[i];
        xy += i * arr[i];
    }

    double m = ((n * xy) - (xSum * ySum)) / ((n * x2Sum) - (xSum * xSum));
    double b = ySum / n - m * xSum / n;

    size_t response_size = snprintf(NULL, 0, "Ecuacuón de la recta: y = %.7lfx + %.7lfb", m, b) + 1;  // +1 for '\0'
    char *response = malloc(response_size);
    sprintf(response, "Ecuacuón de la recta: y = %.7lfx + %.7lfb", m, b);
    write_raw_response(client, response);
    free(response);
}
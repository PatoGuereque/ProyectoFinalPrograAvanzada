#include <stdio.h>
#include <time.h>

void write_curr_time(char *tstring) {
    /* get seconds since the Epoch */
    time_t secs = time(0);

    /* convert to localtime */
    struct tm *local = localtime(&secs);

    /* and set the string */
    sprintf(tstring, "%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
}
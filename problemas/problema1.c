#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../utils.h"

void problema1(const int connfd, const int n) {
  time_t currentTime;
  time(&currentTime);
  struct tm *myTime = localtime(&currentTime);

  int hour = myTime->tm_hour;
  if(hour < 5){
    printf("Mi hora actual es: %i:%i:%i", myTime->tm_hour+19, myTime->tm_min, myTime->tm_sec);
  } else {
    printf("Mi hora actual es: %i:%i:%i", myTime->tm_hour-5, myTime->tm_min, myTime->tm_sec);
  }
}
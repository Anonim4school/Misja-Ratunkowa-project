/*  Generatory liczb losowych, funkcje pomocnicze. */

#include <stdlib.h>
#include "../include/utilis.h"

double random_double(){
  return (double)rand() / (double)RAND_MAX;
}

double random_range(double min, double max){
  return min + random_double() * (max - min);
}
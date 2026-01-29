/*  Generatory liczb losowych, funkcje pomocnicze. */
#include <stdlib.h>
#include <stdio.h>
#include "../include/utilis.h"
#include "../include/pso.h"

double random_double(){
  return (double)rand() / (double)RAND_MAX;
}

double random_range(double min, double max){
  return min + random_double() * (max - min);
}

void load_config(const char *filename, Swarm *s) {
    FILE *f = fopen(filename, "r");
    if (f) {
        if(fscanf(f, "%lf %lf %lf", &s->weight, &s->c1_weight, &s->c2_weight) == 3) {
            printf("Wczytano konfigurację: w=%.2f, c1=%.2f, c2=%.2f\n", 
                   s->weight, s->c1_weight, s->c2_weight);
        } else {
             printf("Błąd formatu pliku konfiguracyjnego. Użyto domyślnych.\n");
        }
        fclose(f);
    } else {
        printf("Nie znaleziono pliku config '%s'. Użyto wartości domyślnych.\n", filename);
    }
}
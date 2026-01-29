/*  Generatory liczb losowych, funkcje pomocnicze. */
#ifndef UTILS_H
#define UTILS_H

#include "pso.h"

double random_double();
double random_range(double min, double max);
void load_config(const char *filename, Swarm *s);

#endif
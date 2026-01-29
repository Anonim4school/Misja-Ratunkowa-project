/* Zapis danych danych pośrednich (informacji o położeniu
cząstek) do pliku */
#ifndef LOGGER_H
#define LOGGER_H

#include "pso.h"

int init_logger(const char *filename);
void log_swarm_state(Swarm *s, int iteration);
void close_logger();

#endif
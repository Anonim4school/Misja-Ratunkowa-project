/* Zapis danych pośrednich (informacji o położeniu
cząstek) do pliku */
#include <stdio.h>
#include <stdlib.h>
#include "../include/logger.h"

static FILE *log_file = NULL;

int init_logger(const char *filename) {
    log_file = fopen(filename, "w");
    if (log_file == NULL) {
        perror("Błąd otwarcia pliku logów");
        return 0;
    }
    // Nagłówek pliku CSV
    fprintf(log_file, "iteracja,id_czastki,x,y,fitness\n");
    return 1;
}

void log_swarm_state(Swarm *s, int iteration) {
    if (log_file == NULL) return;

    for (int i = 0; i < s->particle_count; i++) {
        Particle p = s->swarm[i];
        fprintf(log_file, "%d,%d,%.4f,%.4f,%.4f\n", 
                iteration, i, p.x, p.y, p.curr_value);
    }
}

void close_logger() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}
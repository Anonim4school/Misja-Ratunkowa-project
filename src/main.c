#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/map.h"
#include "../include/pso.h"
#include "../include/utilis.h"
#include "../include/logger.h"

// Funkcja pomocnicza do wczytania parametrów z pliku


int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc < 2) {
        fprintf(stderr, "Użycie: %s <plik_mapy> [-p liczba_czastek] [-i iteracje] [-c config] [-n log_step]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *map_filename = argv[1];
    int particle_count = 30;
    int iterations = 100;
    char *config_filename = NULL;
    int log_step = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            particle_count = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            iterations = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            config_filename = argv[++i];
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            log_step = atoi(argv[++i]);
        }
    }

    int width, height;
    double **map;
    
    load_map(map_filename, &map, &width, &height);

    Swarm *swarm = init_swarm(particle_count, width, height, map);

    if (config_filename != NULL) {
        load_config(config_filename, swarm);
    }

    if (log_step > 0) {
        if (!init_logger("data/pso_log.csv")) {
            fprintf(stderr, "Ostrzeżenie: Nie można utworzyć pliku logów.\n");
            log_step = 0;
        }
    }

    printf("Mapa: %dx%d | Cząstek: %d | Iteracji: %d\n", width, height, particle_count, iterations);

    for (int t = 0; t < iterations; t++) {
        update(swarm, map, width, height);

        if (log_step > 0 && (t % log_step == 0)) {
            log_swarm_state(swarm, t);
        }
    }

    printf("\nZnalezione maksimum (wartość): %.4f\n", swarm->global_best);
    printf("Współrzędne (x, y): (%.2f, %.2f)\n", swarm->global_best_x, swarm->global_best_y);

    if (log_step > 0) close_logger();
    free_swarm(swarm);
    free_map(map, height);

    return EXIT_SUCCESS;
}
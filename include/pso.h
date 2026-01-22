/* Logika algorytmu, struktury cząstki i roju */
#ifndef PSO_H
#define PSO_H

#include <stdlib.h>


typedef struct {
  double x;
  double y;
  double velocity_x;
  double velocity_y;

  double best_x;
  double best_y;
  double best_value;
  double curr_value;
}Particle;

typedef struct {

  Particle *swarm;
  int particle_count;

  double global_best;
  double global_best_x;
  double global_best_y;

  double weight;
  double c1_weight; //jak bardzo ufa sobie
  double c2_weight;  //wiedza roju ufam innym
}Swarm;


Swarm* init_swarm(int particle_count, int map_width, int map_height, double **map_data);
void free_swarm(Swarm *swarm);
void update(Swarm *swarm, double **map_data, int map_width, int map_height);

#endif
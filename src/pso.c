/* Logika algorytmu, struktury cząstki i roju */

#include <stdio.h>
#include <stdlib.h>
#include "../include/pso.h"    
#include "../include/map.h"
#include "../include/utilis.h"

Swarm* init_swarm(int particle_count,int map_width, int map_height,double **map_data){
  Swarm *s = (Swarm*)malloc(sizeof(Swarm));

  s->swarm = (Particle*)malloc(sizeof(Particle) * particle_count);
  s->particle_count = particle_count;


  s->weight = 0.5;
  s->c1_weight = 1.0;
  s->c2_weight = 1.0;

  s->global_best = -1000000000.0;

  for(int i = 0; i < particle_count; i++){
        Particle *p = &s->swarm[i]; 

        // Losowanie pozycji
        p->x = random_range(0, map_width - 1);
        p->y = random_range(0, map_height - 1);

        // Losowanie prędkości
        p->velocity_x = random_range(-1.0, 1.0);
        p->velocity_y = random_range(-1.0, 1.0);


        double val = get_map_value(map_data, (int)p->x, (int)p->y, map_width, map_height);
        
        p->curr_value = val;
        p->best_value = val;
        p->best_x = p->x;
        p->best_y = p->y;

        if(val > s->global_best){
            s->global_best = val;
            s->global_best_x = p->x;
            s->global_best_y = p->y;
        }
    }

    return s;
}

void update(Swarm *s, double **map_data, int map_width, int map_height){
    for(int i = 0; i < s->particle_count; i++){
        Particle *p = &s->swarm[i]; 

       
        double r1 = random_double();
        double r2 = random_double();

        //Aktualizacja prędkości X
        p->velocity_x = (s->weight * p->velocity_x) + 
                        (s->c1_weight * r1 * (p->best_x - p->x)) + 
                        (s->c2_weight * r2 * (s->global_best_x - p->x));


        r1 = random_double();
        r2 = random_double();


        p->velocity_y = (s->weight * p->velocity_y) + 
                        (s->c1_weight * r1 * (p->best_y - p->y)) + 
                        (s->c2_weight * r2 * (s->global_best_y - p->y));


        p->x = p->x + p->velocity_x;
        p->y = p->y + p->velocity_y;


        double current_val = get_map_value(map_data, (int)p->x, (int)p->y, map_width, map_height);
        p->curr_value = current_val;

        // Aktualizacja pBest (najlepszy wynik cząstki)
        if(current_val > p->best_value){
            p->best_value = current_val;
            p->best_x = p->x;
            p->best_y = p->y;

            // Aktualizacja gBest (najlepszy wynik roju)
            if(current_val > s->global_best){
                s->global_best = current_val;
                s->global_best_x = p->x;
                s->global_best_y = p->y;
            }
        }
    }
}

void free_swarm(Swarm *s){
    if(s != NULL){
        if(s->swarm != NULL){
            free(s->swarm); 
        }
        free(s); 
    }
}




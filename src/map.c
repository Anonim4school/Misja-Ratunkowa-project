/* Obsługa wczytywania mapy, zwalniania pamięci mapy,
pobierania wartości z danego punktu. */
#include <stdio.h>
#include <stdlib.h>
#include "../include/map.h"

void load_map(const char *filename, double ***map, int *width, int *height){
    FILE *file=fopen(filename, "r");
    if(file==NULL){
        perror("Nie można otworzyć pliku mapy");
        exit(EXIT_FAILURE);
    }
    else{
        fscanf(file,"%d %d", width, height);
        *map=(double **)malloc((*height)*sizeof(double *));
        for(int i=0;i<*height;i++){
            (*map)[i]=(double *)malloc((*width)*sizeof(double));
            for(int j=0;j<*width;j++){
                fscanf(file,"%lf", &(*map)[i][j]);
            }
        }
        fclose(file);
    }
}

void free_map(double **map, int height){
    for(int i=0;i<height;i++){
        free(map[i]);
    }
    free(map);
}

double get_map_value(double **map, int x, int y, int width, int height){
    if(x<0 || x>=width || y<0 || y>=height){
        return -1000000000.0;
    }
    return map[x][y];
}

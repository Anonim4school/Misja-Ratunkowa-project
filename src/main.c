//Obsługa argumentów wywołania, inicjalizacja, główna pętla.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/map.h"
#include "../include/pso.h"

int main(int argc, char *argv[]) {
    int height,width;
    double **map;
    char *filename=argv[1];

    load_map(filename, &map, &height, &width);
    
    //Wyświetlanie mapy to można usunąć później, tylko takie do obczajenia co i jak
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            printf("%.2f ", map[i][j]);
        }
        printf("\n");
    }
    //Wypisanie wartości z mapy w punkcie (1,5) (wiersz, kolumna) lizcone od (0,0) tez do usunięcia później
    printf("Wartość mapy w punkcie (1,5): %.2f\n", get_map_value(map, 1,5, width, height));

    free_map(map, height);
    return EXIT_SUCCESS;
}
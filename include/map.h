/* Obsługa wczytywania mapy, zwalniania pamięci mapy,
pobierania wartości z danego punktu. */
#ifndef MAP_H
#define MAP_H

void(load_map)(const char *filename, double ***map, int *width, int *height);
void(free_map)(double **map, int height);
double(get_map_value)(double **map, int x, int y, int width, int height);

#endif
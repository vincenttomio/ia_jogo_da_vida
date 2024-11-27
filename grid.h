#ifndef GRID_H
#define GRID_H

#define ALIVE 1
#define DEAD 0

int **allocate_grid(int n, int m);
void free_grid(int **grid, int n);
int count_neighbors(int **grid, int x, int y, int n, int m);
void evolve(int **current, int **next, int n, int m);
void next_generation(int **matrix, int **new_matrix, int n, int m); // Nova função
void print_grid(int **grid, int n, int m); // Nova função de impressão
void copy_grid(int **dest, int **src, int n, int m);


#endif

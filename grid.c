#include <stdlib.h>
#include <stdio.h>
#include "grid.h"

int **allocate_grid(int n, int m) {
    int **grid = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grid[i] = (int *)calloc(m, sizeof(int));
    }
    return grid;
}

void free_grid(int **grid, int n) {
    for (int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);
}

int count_neighbors(int **grid, int x, int y, int n, int m) {
    int neighbors = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if ((i != x || j != y) && i >= 0 && i < n && j >= 0 && j < m) {
                neighbors += grid[i][j];
            }
        }
    }
    return neighbors;
}

void evolve(int **current, int **next, int n, int m) {
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            int neighbors = count_neighbors(current, i, j, n, m);
            next[i][j] = (current[i][j] == ALIVE) ? 
                         ((neighbors == 2 || neighbors == 3) ? ALIVE : DEAD) : 
                         ((neighbors == 3) ? ALIVE : DEAD);
        }
    }
}

void next_generation(int **matrix, int **new_matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int live_neighbors = count_neighbors(matrix, i, j, n, m);

            if (matrix[i][j] == ALIVE) {
                new_matrix[i][j] = (live_neighbors < 2 || live_neighbors > 3) ? DEAD : ALIVE;
            } else {
                new_matrix[i][j] = (live_neighbors == 3) ? ALIVE : DEAD;
            }
        }
    }
}

void print_grid(int **grid, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Copia o conteúdo de uma matriz para outra
void copy_grid(int **dest, int **src, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

// Função para contar o número de células vivas em uma matriz
int count_live_cells(int **grid, int n, int m) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            count += grid[i][j];
        }
    }
    return count;
}
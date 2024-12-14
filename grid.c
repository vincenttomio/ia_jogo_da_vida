#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include "simulated_annealing.h"
#include "log_utils.h"

// Aloca memória para uma matriz
int **allocate_grid(int num_rows, int num_cols) {
    int **grid = (int **)malloc(num_rows * sizeof(int *));
    for (int i = 0; i < num_rows; i++) {
        grid[i] = (int *)calloc(num_cols, sizeof(int));
    }
    return grid;
}

// Libera a memória de uma matriz
void free_grid(int **grid, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        free(grid[i]);
    }
    free(grid);
}

// Imprime a matriz no console
void print_grid(int **grid, int num_rows, int num_cols) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Registra a matriz em um arquivo de log
void log_grid(int **grid, int num_rows, int num_cols) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            log_message("%d ", grid[i][j]);
        }
        log_message("\n");
    }
}

// Copia os valores de uma matriz para outra
void copy_grid(int **dest, int **src, int num_rows, int num_cols) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

// Conta os vizinhos vivos de uma célula
int count_neighbors(int **grid, int row, int col, int num_rows, int num_cols) {
    int neighbors = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if ((i != row || j != col) && i >= 0 && i < num_rows && j >= 0 && j < num_cols) {
                neighbors += grid[i][j];
            }
        }
    }
    return neighbors;
}

// Atualiza o estado da matriz com base nas regras do jogo
void evolve(int **current, int **next, int num_rows, int num_cols) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            int neighbors = count_neighbors(current, i, j, num_rows, num_cols);
            next[i][j] = (current[i][j] == ALIVE) ?
                         ((neighbors == 2 || neighbors == 3) ? ALIVE : DEAD) :
                         ((neighbors == 3) ? ALIVE : DEAD);
        }
    }
}

// Calcula a próxima geração de uma matriz
void next_generation(int **matrix, int **new_matrix, int num_rows, int num_cols) {
    evolve(matrix, new_matrix, num_rows, num_cols);
}

// Conta o número total de células vivas na matriz
int count_live_cells(int **grid, int num_rows, int num_cols) {
    int count = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            count += grid[i][j];
        }
    }
    return count;
}

// Realiza tentativas de encontrar o estado anterior da matriz
void run_trials(int **prev_position, int **current_position, int **check_position, 
                int **best_prev_position, int num_rows, int num_cols, 
                double max_iter, double initial_temp, double cooling_rate, int max_trials) {
    for (int trial = 1; trial <= max_trials; trial++) {
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                prev_position[i][j] = rand() % 2;
            }
        }

        simulated_annealing(prev_position, current_position, num_rows, num_cols, max_iter, initial_temp, cooling_rate);
        next_generation(prev_position, check_position, num_rows, num_cols);

        if (memcmp_grid(check_position, current_position, num_rows, num_cols)) {
            copy_grid(best_prev_position, prev_position, num_rows, num_cols);
            return;
        }
    }
}

// Compara duas matrizes para verificar igualdade
int memcmp_grid(int **grid1, int **grid2, int num_rows, int num_cols) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (grid1[i][j] != grid2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// Inicializa a matriz anterior com base na matriz atual
void intelligent_initialize(int **prev_position, int **current_position, int num_rows, int num_cols) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            int prob = count_neighbors(current_position, i, j, num_rows, num_cols);
            prev_position[i][j] = (rand() % 10 < prob) ? ALIVE : DEAD;
        }
    }
}

// Realiza tentativas adaptativas para encontrar o estado anterior da matriz
void run_trials_adaptive(int **prev_position, int **current_position, int **check_position, 
                         int **best_prev_position, int num_rows, int num_cols, 
                         double max_iter, double initial_temp, double cooling_rate, int max_trials) {
    run_trials(prev_position, current_position, check_position, best_prev_position, num_rows, num_cols, max_iter, initial_temp, cooling_rate, max_trials);
}

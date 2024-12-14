#ifndef GRID_H
#define GRID_H

#define ALIVE 1
#define DEAD 0

// Aloca uma matriz
int **allocate_grid(int num_rows, int num_cols);

// Libera a memória de uma matriz
void free_grid(int **grid, int num_rows);

// Conta os vizinhos vivos de uma célula
int count_neighbors(int **grid, int row, int col, int num_rows, int num_cols);

// Atualiza o estado da matriz com base nas regras do jogo
void evolve(int **current, int **next, int num_rows, int num_cols);

// Calcula a próxima geração de uma matriz
void next_generation(int **matrix, int **new_matrix, int num_rows, int num_cols);

// Imprime a matriz no console
void print_grid(int **grid, int num_rows, int num_cols);

// Registra a matriz em um arquivo de log
void log_grid(int **grid, int num_rows, int num_cols);

// Copia os valores de uma matriz para outra
void copy_grid(int **dest, int **src, int num_rows, int num_cols);

// Conta o número total de células vivas na matriz
int count_live_cells(int **grid, int num_rows, int num_cols);

// Realiza tentativas de encontrar o estado anterior da matriz
void run_trials(int **prev_position, int **current_position, int **check_position, 
                int **best_prev_position, int num_rows, int num_cols, 
                double max_iter, double initial_temp, double cooling_rate, int max_trials);

// Compara duas matrizes para verificar igualdade
int memcmp_grid(int **grid1, int **grid2, int num_rows, int num_cols);

// Inicializa a matriz anterior com base na matriz atual
void intelligent_initialize(int **prev_position, int **current_position, int num_rows, int num_cols);

// Realiza tentativas adaptativas para encontrar o estado anterior da matriz
void run_trials_adaptive(int **prev_position, int **current_position, int **check_position, 
                         int **best_prev_position, int num_rows, int num_cols, 
                         double max_iter, double initial_temp, double cooling_rate, int max_trials);

#endif // GRID_H

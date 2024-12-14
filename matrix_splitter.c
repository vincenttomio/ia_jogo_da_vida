#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grid.h"
#include "matrix_splitter.h"
#include "log_utils.h"


#define min(a,b) ((a) < (b) ? (a) : (b))

// Define offsets para os 8 vizinhos
const int neighbor_dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int neighbor_dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};


// Função auxiliar para verificar se a célula está dentro dos limites
int is_within_bounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

// Detecta padrões conectados na matrix
int detect_patterns(int **matrix, int rows, int cols, SubMatrix **submatrices, int max_submatrices) {
    int pattern_count = 0;
    int **visited = allocate_grid(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1 && visited[i][j] == 0) {
                if (pattern_count >= max_submatrices) {
                    free_grid(visited, rows);
                    return -1; // Excedeu o limite de submatrixes
                }

                // Inicializa limites do padrão
                int min_row = i, max_row = i, min_col = j, max_col = j;
                visited[i][j] = 1;

                // Pilha para a DFS
                int stack[rows * cols][2], top = 0;
                stack[top][0] = i;
                stack[top][1] = j;
                top++;

                // Executa DFS
                while (top > 0) {
                    top--;
                    int x = stack[top][0];
                    int y = stack[top][1];

                    for (int k = 0; k < 8; k++) {
                        int nx = x + neighbor_dx[k], ny = y + neighbor_dy[k];
                        if (is_within_bounds(nx, ny, rows, cols) && matrix[nx][ny] == 1 && visited[nx][ny] == 0) {
                            visited[nx][ny] = 1;
                            stack[top][0] = nx;
                            stack[top][1] = ny;
                            top++;
                            
                            // Atualiza limites do padrão
                            if (nx < min_row) min_row = nx;
                            if (nx > max_row) max_row = nx;
                            if (ny < min_col) min_col = ny;
                            if (ny > max_col) max_col = ny;
                        }
                    }
                }

                // Cria a submatrix correspondente
                int sub_rows = max_row - min_row + 3; // +2 para bordas
                int sub_cols = max_col - min_col + 3; // +2 para bordas
                
                if (sub_rows * sub_cols > 36) {
                    return -1; // Retorna erro se qualquer padrão exceder o limite
                }

                SubMatrix *submatrix = (SubMatrix *)malloc(sizeof(SubMatrix));
                submatrix->rows = sub_rows;
                submatrix->cols = sub_cols;
                submatrix->start_row = min_row - 1; // Inclui borda
                submatrix->start_col = min_col - 1; // Inclui borda
                submatrix->data = allocate_grid(sub_rows, sub_cols);

                // Preenche a submatrix com os dados do padrão
                for (int r = 0; r < sub_rows; r++) {
                    for (int c = 0; c < sub_cols; c++) {
                        int src_r = min_row + r - 1;
                        int src_c = min_col + c - 1;
                        submatrix->data[r][c] = (is_within_bounds(src_r, src_c, rows, cols)) ? matrix[src_r][src_c] : 0;
                    }
                }

                // Armazena a submatrix apenas se contiver células vivas
                int contains_alive = 0;
                for (int r = 0; r < sub_rows && !contains_alive; r++) {
                    for (int c = 0; c < sub_cols; c++) {
                        if (submatrix->data[r][c] == 1) {
                            contains_alive = 1;
                            break;
                        }
                    }
                }

                if (contains_alive) {
                    submatrices[pattern_count++] = submatrix;
                } else {
                    free_grid(submatrix->data, sub_rows);
                    free(submatrix);
                }
            }
        }
    }

    free_grid(visited, rows);
    return pattern_count;
}

// Função para calcular número de sub-matrixes
int calcular_numero_submatrixes(int n, int m) {
    // Verificar se matrix é pequena demais
    if (n * m <= 36) {
        return 0;
    }
    
    // Ajustar limites considerando bordas
    int rows_uteis = n - 2;
    int cols_uteis = m - 2;
    
    // Número de divisões completas
    int rows_div = rows_uteis / 4;
    int cols_div = cols_uteis / 4;
    
    // Resto das divisões
    int resto_rows = rows_uteis % 4;
    int resto_cols = cols_uteis % 4;
    
    // Contagem de sub-matrixes
    int total_submatrixes = 0;
    
    // Sub-matrixes completas de 4x4
    total_submatrixes += rows_div * cols_div;
    
    // Sub-matrixes na borda inferior
    if (resto_rows > 0) {
        total_submatrixes += cols_div;
    }
    
    // Sub-matrixes na borda direita
    if (resto_cols > 0) {
        total_submatrixes += rows_div;
    }
    
    // Sub-matrix do canto inferior direito
    if (resto_rows > 0 && resto_cols > 0) {
        total_submatrixes += 1;
    }
    
    return total_submatrixes;
}

// Função para extrair sub-matrix com borda
int** extrair_submatrix(int **matrix_original, 
                        int row_inicio, int col_inicio, 
                        int altura, int largura) {
    // Alocar matrix com duas rows/cols extras para borda
    int **submatrix = allocate_grid(altura + 2, largura + 2);
    
    // Inicializar borda com zeros
    for (int i = 0; i < altura + 2; i++) {
        for (int j = 0; j < largura + 2; j++) {
            submatrix[i][j] = 0;
        }
    }
    
    // Copiar conteúdo da sub-matrix original
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            submatrix[i+1][j+1] = matrix_original[row_inicio + i][col_inicio + j];
        }
    }
    
    return submatrix;
}

// Função para dividir matrix em sub-matrixes
void dividir_matrix(int **matrix_original, int **result_matrix, int rows, int cols) {
    int rows_uteis = rows - 2;
    int cols_uteis = cols - 2;
    int rows_div = rows_uteis / 4;
    int cols_div = cols_uteis / 4;
    int resto_rows = rows_uteis % 4;
    int resto_cols = cols_uteis % 4;

    // Processar submatrixes completas de 4x4
    for (int i = 0; i < rows_div; i++) {
        for (int j = 0; j < cols_div; j++) {
            int row_inicio = 1 + i * 4;
            int col_inicio = 1 + j * 4;
            SubMatrix *sub = (SubMatrix *)malloc(sizeof(SubMatrix));
            sub->rows = 6;
            sub->cols = 6;
            sub->start_row = row_inicio - 1;
            sub->start_col = col_inicio - 1;
            sub->data = extrair_submatrix(matrix_original, row_inicio, col_inicio, 4, 4);

            run_and_copy(matrix_original, result_matrix, sub, rows, cols);
        }
    }

    // Processar submatrixes restantes nas bordas
    if (resto_rows > 0) {
        for (int j = 0; j < cols_div; j++) {
            int row_inicio = 1 + rows_div * 4;
            int col_inicio = 1 + j * 4;
            SubMatrix *sub = (SubMatrix *)malloc(sizeof(SubMatrix));
            sub->rows = resto_rows + 2;
            sub->cols = 6;
            sub->start_row = row_inicio - 1;
            sub->start_col = col_inicio - 1;
            sub->data = extrair_submatrix(matrix_original, row_inicio, col_inicio, resto_rows, 4);

            run_and_copy(matrix_original, result_matrix, sub, rows, cols);
        }
    }

    if (resto_cols > 0) {
        for (int i = 0; i < rows_div; i++) {
            int row_inicio = 1 + i * 4;
            int col_inicio = 1 + cols_div * 4;
            SubMatrix *sub = (SubMatrix *)malloc(sizeof(SubMatrix));
            sub->rows = 6;
            sub->cols = resto_cols + 2;
            sub->start_row = row_inicio - 1;
            sub->start_col = col_inicio - 1;
            sub->data = extrair_submatrix(matrix_original, row_inicio, col_inicio, 4, resto_cols);

            run_and_copy(matrix_original, result_matrix, sub, rows, cols);
        }
    }

    if (resto_rows > 0 && resto_cols > 0) {
        int row_inicio = 1 + rows_div * 4;
        int col_inicio = 1 + cols_div * 4;
        SubMatrix *sub = (SubMatrix *)malloc(sizeof(SubMatrix));
        sub->rows = resto_rows + 2;
        sub->cols = resto_cols + 2;
        sub->start_row = row_inicio - 1;
        sub->start_col = col_inicio - 1;
        sub->data = extrair_submatrix(matrix_original, row_inicio, col_inicio, resto_rows, resto_cols);

        run_and_copy(matrix_original, result_matrix, sub, rows, cols);
    }
}

// Nova função para analisar e dividir matrix
void analyze_and_split_matrix(int **matrix, int rows, int cols) {
    if (rows * cols <= 36) {
        log_message("Matriz original:\n");
        log_grid(matrix, rows, cols);
    } else {
        log_message("Analisando padrões e dividindo matrix:\n");
        SubMatrix *submatrices[100]; // Array para armazenar submatrixes
        int pattern_count = detect_patterns(matrix, rows, cols, submatrices, 100);

        if (pattern_count > 0) {
            log_message("Padrões detectados: %d\n", pattern_count);
            for (int i = 0; i < pattern_count; i++) {
                log_message("Padrão %d:\n", i + 1);
                log_grid(submatrices[i]->data, submatrices[i]->rows, submatrices[i]->cols);
                free_grid(submatrices[i]->data, submatrices[i]->rows);
                free(submatrices[i]);
            }
        } else {
            log_message("Dividindo matrix em submatrixes:\n");
            for (int i = 0; i < pattern_count; i++) {
                free_grid(submatrices[i]->data, submatrices[i]->rows);
                free(submatrices[i]);
            }
        }
    }
}

void run_and_copy(int **original_matrix, int **result_matrix, SubMatrix *sub, int rows, int cols) {
    // Resolve a submatrix usando Simulated Annealing
    int **sub_prev_pos = allocate_grid(sub->rows, sub->cols);
    int **sub_current_pos = sub->data;
    int **sub_check_pos = allocate_grid(sub->rows, sub->cols);
    int **sub_best_prev_pos = allocate_grid(sub->rows, sub->cols);

    run_trials_adaptive(sub_prev_pos, sub_current_pos, sub_check_pos, sub_best_prev_pos, 
                        sub->rows, sub->cols, 10000000, 1000000.0, 0.9995, 100);

    // Copiar resultado de volta para a matrix original
    for (int r = 0; r < sub->rows; r++) {
        for (int c = 0; c < sub->cols; c++) {
            int global_r = sub->start_row + r;
            int global_c = sub->start_col + c;
            if (global_r >= 0 && global_r < rows && global_c >= 0 && global_c < cols) {
                result_matrix[global_r][global_c] = sub_best_prev_pos[r][c];
            }
        }
    }

    // Liberar memória temporária
    free_grid(sub_prev_pos, sub->rows);
    free_grid(sub_check_pos, sub->rows);
    free_grid(sub_best_prev_pos, sub->rows);
    free_grid(sub->data, sub->rows);
    free(sub);
}

// Nova função para resolver e reconstruir matrix
int** solve_divided_matrix(int **original_matrix, int rows, int cols) {
    int **result_matrix = allocate_grid(rows, cols);
    SubMatrix *submatrices[100];
    int pattern_count = detect_patterns(original_matrix, rows, cols, submatrices, 100);

    if (pattern_count <= 0) {
        dividir_matrix(original_matrix, result_matrix, rows, cols);
    } else {
        for (int i = 0; i < pattern_count; i++) {
            run_and_copy(original_matrix, result_matrix, submatrices[i], rows, cols);
        }
    }

    return result_matrix;
}
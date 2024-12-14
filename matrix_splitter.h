#ifndef MATRIX_SPLITTER_H
#define MATRIX_SPLITTER_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar submatrizes
typedef struct {
    int **data;  // Ponteiro para a matriz
    int rows;    // Número de linhas
    int cols;    // Número de colunas
    int start_row; // Linha inicial na matriz original
    int start_col; // Coluna inicial na matriz original
} SubMatrix;

// Função para detectar padrões (componentes conectados)
int detect_patterns(int **matrix, int rows, int cols, SubMatrix **submatrices, int max_submatrices);

// Função para dividir a matriz em submatrizes de tamanho fixo com borda
int divide_matrix(int **matrix, int rows, int cols, int sub_rows, int sub_cols, SubMatrix **submatrices);

// Nova função para analisar e dividir matrizes (lógica do main do arquivo de teste)
void analyze_and_split_matrix(int **matrix, int rows, int cols);

int** solve_divided_matrix(int **original_matrix, int rows, int cols);

int is_valid(int x, int y, int rows, int cols);

void run_and_copy(int **original_matrix, int **result_matrix, SubMatrix *sub, int rows, int cols);


#endif // MATRIX_SPLITTER_H
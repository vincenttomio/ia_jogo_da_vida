#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "cost.h"
#include "perturbation.h"
#include "simulated_annealing.h"

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

int main() {
    int n, m;

    puts("Lendo matriz de entrada");
    scanf("%d %d", &n, &m);

    int **current_position = allocate_grid(n, m);
    int **prev_position = allocate_grid(n, m);
    int **check_position = allocate_grid(n, m); // Matriz para verificar o estado evoluído
    int **best_prev_position = allocate_grid(n, m); // Melhor estado anterior encontrado

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &current_position[i][j]);
        }
    }

    printf("Imprimindo matriz de entrada:\n");
    print_grid(current_position, n, m);

    double max_iter = 10000000;
    double initial_temp = 1000000.0;
    double cooling_rate = 0.9995;
    int max_trials = 10; // Número máximo de iterações para tentar encontrar o melhor estado
    int min_live_cells = n * m; // Inicializa com o máximo possível de células vivas

    srand(time(NULL));

    for (int trial = 1; trial <= max_trials; trial++) {
        printf("\n--- Tentativa %d ---\n", trial);

        // Encontra um possível estado anterior
        simulated_annealing(prev_position, current_position, n, m, max_iter, initial_temp, cooling_rate);

        // Gera o próximo estado a partir do estado anterior encontrado
        next_generation(prev_position, check_position, n, m);

        printf("Estado anterior encontrado:\n");
        print_grid(prev_position, n, m);

        printf("Estado posterior ao anterior encontrado:\n");
        print_grid(check_position, n, m);

        // Verifica se o estado gerado é igual ao estado atual
        int is_valid = 1;
        for (int i = 0; i < n && is_valid; i++) {
            for (int j = 0; j < m; j++) {
                if (check_position[i][j] != current_position[i][j]) {
                    is_valid = 0;
                    break;
                }
            }
        }

        if (is_valid) {
            printf("O estado anterior encontrado é válido.\n");

            // Conta o número de células vivas no estado anterior
            int live_cells = count_live_cells(prev_position, n, m);
            printf("Número de células vivas no estado anterior: %d\n", live_cells);

            // Atualiza o melhor estado anterior se for válido e tiver menos células vivas
            if (live_cells < min_live_cells) {
                min_live_cells = live_cells;
                copy_grid(best_prev_position, prev_position, n, m);
                printf("Novo melhor estado encontrado!\n");
            }
        } else {
            printf("O estado anterior encontrado não evolui para o estado atual corretamente.\n");
        }
    }

    printf("\n--- Melhor estado anterior encontrado ---\n");
    print_grid(best_prev_position, n, m);
    printf("Número de células vivas no melhor estado: %d\n", min_live_cells);

    // Liberar memória
    free_grid(prev_position, n);
    free_grid(current_position, n);
    free_grid(check_position, n);
    free_grid(best_prev_position, n);

    return 0;
}

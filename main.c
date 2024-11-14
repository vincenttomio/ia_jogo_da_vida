#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "cost.h"
#include "perturbation.h"
#include "simulated_annealing.h"

int main() {
    int n, m;

    puts("Lendo matriz de entrada");
    scanf("%d %d", &n, &m);

    int **current_position = allocate_grid(n, m);
    int **prev_position = allocate_grid(n, m);
    int **check_position = allocate_grid(n, m); // Matriz para verificar o estado evoluído

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &current_position[i][j]);
        }
    }

    printf("Imprimindo matriz de entrada:\n");
    print_grid(current_position, n, m);

    int max_iter = 10000000;
    double initial_temp = 1000000.0;
    double cooling_rate = 0.9999;

    srand(time(NULL));

    // Encontra um possível estado anterior
    simulated_annealing(prev_position, current_position, n, m, max_iter, initial_temp, cooling_rate);

    // Gera o próximo estado a partir do estado anterior encontrado
    next_generation(prev_position, check_position, n, m);

    printf("Estado anterior encontrado:\n");
    print_grid(prev_position, n, m);

    printf("Estado posteriror ao anterior encontrado:\n");
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
    } else {
        printf("O estado anterior encontrado não evolui para o estado atual corretamente.\n");
    }

    // Liberar memória
    free_grid(prev_position, n);
    free_grid(current_position, n);
    free_grid(check_position, n);

    return 0;
}

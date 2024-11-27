#include <math.h>
#include "cost.h"
#include "grid.h"

#ifndef INFINITY
#define INFINITY (__builtin_inff())
#endif

double calculate_cost(int **state, int **goal, int **next, int n, int m) {
    evolve(state, next, n, m); // Gera a próxima geração
    double difference_cost = 0.0, live_cells_cost = 0.0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (next[i][j] != goal[i][j]) {
                difference_cost += 1.0; // Cada célula diferente adiciona ao custo
            }
            if (state[i][j] == ALIVE) {
                live_cells_cost += 1.0; // Células vivas têm custo adicional
            }
        }
    }

    double alpha = 20.0; // Peso do custo de diferença
    double beta = 1.0;   // Peso do custo de células vivas

    double total_cost = alpha * difference_cost + beta * live_cells_cost;

    // Se o custo for extremamente alto, podemos retornar INFINITY como penalidade
    if (total_cost > 1e6) { 
        return INFINITY;
    }

    return total_cost;
}